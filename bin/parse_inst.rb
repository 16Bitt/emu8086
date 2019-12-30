class Instruction
  attr_reader :opcode, :mnemonic, :addr_mode

  def initialize(opcode, mnemonic, addr_mode)
    @opcode = opcode
    @mnemonic = clean(mnemonic)
    @addr_mode = clean(addr_mode)
  end

  def to_s
    <<-C
    case 0x#{opcode.downcase}:
      inst->op = #{c_op};
      inst->mode = #{c_mode};
      return;
    C
  end

  class << self
    def from_line(line)
      parts = line.chomp.split("\t")
      Instruction.new(
        parts.first,
        parts[1],
        parts.drop(2).reject(&:empty?).join(',')
      )
    end
  end

  private

  def c_op
    "OP_#{mnemonic}"
  end

  def c_mode
    return 'ADDR_NONE' if addr_mode.empty?
    "ADDR_#{addr_mode}"
  end

  def clean(name)
    name.gsub(/[\/,\s:]/, '_').upcase
  end
end

instructions = []
File.open(ARGV.first, 'r') do |f|
  f.each do |line|
    next if line.chomp.empty? || line.include?('--') || line.start_with?('GRP')
    instructions << Instruction.from_line(line)
  end
end

case ARGV[1]
when 'decode'
  puts(
    <<~C
    #include "emu8086.h"
    
    /*
     * This function is auto-generated! DO NOT EDIT DIRECTLY
     */
    void instruction_decode_generated(uint8_t op, struct instruction *inst) {
      switch(op) {
    C
  )
  instructions.each { |inst| puts(inst) }
  puts(
    <<~C
        default:
          inst->op = OP_UNKNOWN;
      }
    }
    C
  )
when 'define'
  puts(
    <<~C
    /*
     * This enum is auto-generated! DO NOT EDIT DIRECTLY
     */

    enum operation_t {
      OP_UNKNOWN,
    C
  )
  puts(instructions.map { |inst| "  OP_#{inst.mnemonic}" }.uniq.join(",\n"))
  puts(
    <<~C
    };

    enum register_mode_t {
      ADDR_NONE,
    C
  )
  puts(instructions.map(&:addr_mode).reject(&:empty?).map { |mode| "  ADDR_#{mode}" }.uniq.join(",\n"))
  puts(
    <<~C
    };

    C
  )
else
  raise 'ARGV[1] must be define or decode'
end
