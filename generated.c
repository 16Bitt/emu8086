#include "emu8086.h"

void handle_decode(uint8_t op) {
  switch(op) {
  case 0x00:
    op_ADD(args_Eb_Gb);
    break;
  case 0x01:
    op_ADD(args_Ev_Gv);
    break;
  case 0x02:
    op_ADD(args_Gb_Eb);
    break;
  case 0x03:
    op_ADD(args_Gv_Ev);
    break;
  case 0x04:
    op_ADD(args_AL_Ib);
    break;
  case 0x05:
    op_ADD(args_eAX_Iv);
    break;
  case 0x08:
    op_OR(args_Eb_Gb);
    break;
  case 0x09:
    op_OR(args_Ev_Gv);
    break;
  case 0x0A:
    op_OR(args_Gb_Eb);
    break;
  case 0x0B:
    op_OR(args_Gv_Ev);
    break;
  case 0x0C:
    op_OR(args_AL_Ib);
    break;
  case 0x0D:
    op_OR(args_eAX_Iv);
    break;
/* Unknown opcode 0F */
  case 0x10:
    op_ADC(args_Eb_Gb);
    break;
  case 0x11:
    op_ADC(args_Ev_Gv);
    break;
  case 0x12:
    op_ADC(args_Gb_Eb);
    break;
  case 0x13:
    op_ADC(args_Gv_Ev);
    break;
  case 0x14:
    op_ADC(args_AL_Ib);
    break;
  case 0x15:
    op_ADC(args_eAX_Iv);
    break;
  case 0x18:
    op_SBB(args_Eb_Gb);
    break;
  case 0x19:
    op_SBB(args_Ev_Gv);
    break;
  case 0x1A:
    op_SBB(args_Gb_Eb);
    break;
  case 0x1B:
    op_SBB(args_Gv_Ev);
    break;
  case 0x1C:
    op_SBB(args_AL_Ib);
    break;
  case 0x1D:
    op_SBB(args_eAX_Iv);
    break;
  case 0x20:
    op_AND(args_Eb_Gb);
    break;
  case 0x21:
    op_AND(args_Ev_Gv);
    break;
  case 0x22:
    op_AND(args_Gb_Eb);
    break;
  case 0x23:
    op_AND(args_Gv_Ev);
    break;
  case 0x24:
    op_AND(args_AL_Ib);
    break;
  case 0x25:
    op_AND(args_eAX_Iv);
    break;
/* Unknown opcode 26 */
  case 0x27:
    op_DAA();
    break;
  case 0x28:
    op_SUB(args_Eb_Gb);
    break;
  case 0x29:
    op_SUB(args_Ev_Gv);
    break;
  case 0x2A:
    op_SUB(args_Gb_Eb);
    break;
  case 0x2B:
    op_SUB(args_Gv_Ev);
    break;
  case 0x2C:
    op_SUB(args_AL_Ib);
    break;
  case 0x2D:
    op_SUB(args_eAX_Iv);
    break;
/* Unknown opcode 2E */
  case 0x2F:
    op_DAS();
    break;
  case 0x30:
    op_XOR(args_Eb_Gb);
    break;
  case 0x31:
    op_XOR(args_Ev_Gv);
    break;
  case 0x32:
    op_XOR(args_Gb_Eb);
    break;
  case 0x33:
    op_XOR(args_Gv_Ev);
    break;
  case 0x34:
    op_XOR(args_AL_Ib);
    break;
  case 0x35:
    op_XOR(args_eAX_Iv);
    break;
/* Unknown opcode 36 */
  case 0x37:
    op_AAA();
    break;
  case 0x38:
    op_CMP(args_Eb_Gb);
    break;
  case 0x39:
    op_CMP(args_Ev_Gv);
    break;
  case 0x3A:
    op_CMP(args_Gb_Eb);
    break;
  case 0x3B:
    op_CMP(args_Gv_Ev);
    break;
  case 0x3C:
    op_CMP(args_AL_Ib);
    break;
  case 0x3D:
    op_CMP(args_eAX_Iv);
    break;
/* Unknown opcode 3E */
  case 0x3F:
    op_AAS();
    break;
/* Unknown opcode 60 */
/* Unknown opcode 61 */
/* Unknown opcode 62 */
/* Unknown opcode 63 */
/* Unknown opcode 64 */
/* Unknown opcode 65 */
/* Unknown opcode 66 */
/* Unknown opcode 67 */
/* Unknown opcode 68 */
/* Unknown opcode 69 */
/* Unknown opcode 6A */
/* Unknown opcode 6B */
/* Unknown opcode 6C */
/* Unknown opcode 6D */
/* Unknown opcode 6E */
/* Unknown opcode 6F */
  case 0x80:
    op_GRP1(args_Eb_Ib);
    break;
  case 0x81:
    op_GRP1(args_Ev_Iv);
    break;
  case 0x82:
    op_GRP1(args_Eb_Ib);
    break;
  case 0x83:
    op_GRP1(args_Ev_Ib);
    break;
  case 0x84:
    op_TEST(args_Gb_Eb);
    break;
  case 0x85:
    op_TEST(args_Gv_Ev);
    break;
  case 0x86:
    op_XCHG(args_Gb_Eb);
    break;
  case 0x87:
    op_XCHG(args_Gv_Ev);
    break;
  case 0x88:
    op_MOV(args_Eb_Gb);
    break;
  case 0x89:
    op_MOV(args_Ev_Gv);
    break;
  case 0x8A:
    op_MOV(args_Gb_Eb);
    break;
  case 0x8B:
    op_MOV(args_Gv_Ev);
    break;
  case 0x8C:
    op_MOV(args_Ew_Sw);
    break;
  case 0x8D:
    op_LEA(args_Gv_M);
    break;
  case 0x8E:
    op_MOV(args_Sw_Ew);
    break;
  case 0x90:
    op_NOP();
    break;
  case 0x91:
    op_XCHG(args_eCX_eAX);
    break;
  case 0x92:
    op_XCHG(args_eDX_eAX);
    break;
  case 0x93:
    op_XCHG(args_eBX_eAX);
    break;
  case 0x94:
    op_XCHG(args_eSP_eAX);
    break;
  case 0x95:
    op_XCHG(args_eBP_eAX);
    break;
  case 0x96:
    op_XCHG(args_eSI_eAX);
    break;
  case 0x97:
    op_XCHG(args_eDI_eAX);
    break;
  case 0x98:
    op_CBW();
    break;
  case 0x99:
    op_CWD();
    break;
  case 0x9B:
    op_WAIT();
    break;
  case 0x9C:
    op_PUSHF();
    break;
  case 0x9D:
    op_POPF();
    break;
  case 0x9E:
    op_SAHF();
    break;
  case 0x9F:
    op_LAHF();
    break;
  case 0xA0:
    op_MOV(args_AL_Ob);
    break;
  case 0xA1:
    op_MOV(args_eAX_Ov);
    break;
  case 0xA2:
    op_MOV(args_Ob_AL);
    break;
  case 0xA3:
    op_MOV(args_Ov_eAX);
    break;
  case 0xA4:
    op_MOVSB();
    break;
  case 0xA5:
    op_MOVSW();
    break;
  case 0xA6:
    op_CMPSB();
    break;
  case 0xA7:
    op_CMPSW();
    break;
  case 0xA8:
    op_TEST(args_AL_Ib);
    break;
  case 0xA9:
    op_TEST(args_eAX_Iv);
    break;
  case 0xAA:
    op_STOSB();
    break;
  case 0xAB:
    op_STOSW();
    break;
  case 0xAC:
    op_LODSB();
    break;
  case 0xAD:
    op_LODSW();
    break;
  case 0xAE:
    op_SCASB();
    break;
  case 0xAF:
    op_SCASW();
    break;
  case 0xB0:
    op_MOV(args_AL_Ib);
    break;
  case 0xB1:
    op_MOV(args_CL_Ib);
    break;
  case 0xB2:
    op_MOV(args_DL_Ib);
    break;
  case 0xB3:
    op_MOV(args_BL_Ib);
    break;
  case 0xB4:
    op_MOV(args_AH_Ib);
    break;
  case 0xB5:
    op_MOV(args_CH_Ib);
    break;
  case 0xB6:
    op_MOV(args_DH_Ib);
    break;
  case 0xB7:
    op_MOV(args_BH_Ib);
    break;
  case 0xB8:
    op_MOV(args_eAX_Iv);
    break;
  case 0xB9:
    op_MOV(args_eCX_Iv);
    break;
  case 0xBA:
    op_MOV(args_eDX_Iv);
    break;
  case 0xBB:
    op_MOV(args_eBX_Iv);
    break;
  case 0xBC:
    op_MOV(args_eSP_Iv);
    break;
  case 0xBD:
    op_MOV(args_eBP_Iv);
    break;
  case 0xBE:
    op_MOV(args_eSI_Iv);
    break;
  case 0xBF:
    op_MOV(args_eDI_Iv);
    break;
/* Unknown opcode C0 */
/* Unknown opcode C1 */
  case 0xC3:
    op_RET();
    break;
  case 0xC4:
    op_LES(args_Gv_Mp);
    break;
  case 0xC5:
    op_LDS(args_Gv_Mp);
    break;
  case 0xC6:
    op_MOV(args_Eb_Ib);
    break;
  case 0xC7:
    op_MOV(args_Ev_Iv);
    break;
/* Unknown opcode C8 */
/* Unknown opcode C9 */
  case 0xCB:
    op_RETF();
    break;
  case 0xCE:
    op_INTO();
    break;
  case 0xCF:
    op_IRET();
    break;
  case 0xD0:
    op_GRP2(args_Eb_1);
    break;
  case 0xD1:
    op_GRP2(args_Ev_1);
    break;
  case 0xD2:
    op_GRP2(args_Eb_CL);
    break;
  case 0xD3:
    op_GRP2(args_Ev_CL);
    break;
/* Unknown opcode D6 */
  case 0xD7:
    op_XLAT();
    break;
/* Unknown opcode D8 */
/* Unknown opcode D9 */
/* Unknown opcode DA */
/* Unknown opcode DB */
/* Unknown opcode DC */
/* Unknown opcode DD */
/* Unknown opcode DE */
/* Unknown opcode DF */
  case 0xE4:
    op_IN(args_AL_Ib);
    break;
  case 0xE5:
    op_IN(args_eAX_Ib);
    break;
  case 0xE6:
    op_OUT(args_Ib_AL);
    break;
  case 0xE7:
    op_OUT(args_Ib_eAX);
    break;
  case 0xEC:
    op_IN(args_AL_DX);
    break;
  case 0xED:
    op_IN(args_eAX_DX);
    break;
  case 0xEE:
    op_OUT(args_DX_AL);
    break;
  case 0xEF:
    op_OUT(args_DX_eAX);
    break;
  case 0xF0:
    op_LOCK();
    break;
/* Unknown opcode F1 */
  case 0xF2:
    op_REPNZ();
    break;
  case 0xF3:
    op_REPZ();
    break;
  case 0xF4:
    op_HLT();
    break;
  case 0xF5:
    op_CMC();
    break;
  case 0xF8:
    op_CLC();
    break;
  case 0xF9:
    op_STC();
    break;
  case 0xFA:
    op_CLI();
    break;
  case 0xFB:
    op_STI();
    break;
  case 0xFC:
    op_CLD();
    break;
  case 0xFD:
    op_STD();
    break;
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Unknown opcode GRP2/6 */
/* Ignore GRP */
/* Ignore GRP */
/* Unknown opcode GRP3a/1 */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Unknown opcode GRP3b/1 */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Unknown opcode GRP4/2 */
/* Unknown opcode GRP4/3 */
/* Unknown opcode GRP4/4 */
/* Unknown opcode GRP4/5 */
/* Unknown opcode GRP4/6 */
/* Unknown opcode GRP4/7 */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Ignore GRP */
/* Unknown opcode GRP5/7 */
  default:
  }
}
