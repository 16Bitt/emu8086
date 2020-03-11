#include "emu8086.h"

void handle_decode(struct ExecutionContext* ec, uint8_t op) {
  switch(op) {
  case 0x00:
    op_ADD(ec, op, args_Eb_Gb);
    break;
  case 0x01:
    op_ADD(ec, op, args_Ev_Gv);
    break;
  case 0x02:
    op_ADD(ec, op, args_Gb_Eb);
    break;
  case 0x03:
    op_ADD(ec, op, args_Gv_Ev);
    break;
  case 0x04:
    op_ADD(ec, op, args_AL_Ib);
    break;
  case 0x05:
    op_ADD(ec, op, args_eAX_Iv);
    break;
  case 0x06:
    op_PUSH(ec, op, args_ES);
    break;
  case 0x07:
    op_POP(ec, op, args_ES);
    break;
  case 0x08:
    op_OR(ec, op, args_Eb_Gb);
    break;
  case 0x09:
    op_OR(ec, op, args_Ev_Gv);
    break;
  case 0x0A:
    op_OR(ec, op, args_Gb_Eb);
    break;
  case 0x0B:
    op_OR(ec, op, args_Gv_Ev);
    break;
  case 0x0C:
    op_OR(ec, op, args_AL_Ib);
    break;
  case 0x0D:
    op_OR(ec, op, args_eAX_Iv);
    break;
  case 0x0E:
    op_PUSH(ec, op, args_CS);
    break;
/* Unknown opcode 0F */
  case 0x10:
    op_ADC(ec, op, args_Eb_Gb);
    break;
  case 0x11:
    op_ADC(ec, op, args_Ev_Gv);
    break;
  case 0x12:
    op_ADC(ec, op, args_Gb_Eb);
    break;
  case 0x13:
    op_ADC(ec, op, args_Gv_Ev);
    break;
  case 0x14:
    op_ADC(ec, op, args_AL_Ib);
    break;
  case 0x15:
    op_ADC(ec, op, args_eAX_Iv);
    break;
  case 0x16:
    op_PUSH(ec, op, args_SS);
    break;
  case 0x17:
    op_POP(ec, op, args_SS);
    break;
  case 0x18:
    op_SBB(ec, op, args_Eb_Gb);
    break;
  case 0x19:
    op_SBB(ec, op, args_Ev_Gv);
    break;
  case 0x1A:
    op_SBB(ec, op, args_Gb_Eb);
    break;
  case 0x1B:
    op_SBB(ec, op, args_Gv_Ev);
    break;
  case 0x1C:
    op_SBB(ec, op, args_AL_Ib);
    break;
  case 0x1D:
    op_SBB(ec, op, args_eAX_Iv);
    break;
  case 0x1E:
    op_PUSH(ec, op, args_DS);
    break;
  case 0x1F:
    op_POP(ec, op, args_DS);
    break;
  case 0x20:
    op_AND(ec, op, args_Eb_Gb);
    break;
  case 0x21:
    op_AND(ec, op, args_Ev_Gv);
    break;
  case 0x22:
    op_AND(ec, op, args_Gb_Eb);
    break;
  case 0x23:
    op_AND(ec, op, args_Gv_Ev);
    break;
  case 0x24:
    op_AND(ec, op, args_AL_Ib);
    break;
  case 0x25:
    op_AND(ec, op, args_eAX_Iv);
    break;
/* Unknown opcode 26 */
  case 0x27:
    op_DAA(ec, op, args_none);
    break;
  case 0x28:
    op_SUB(ec, op, args_Eb_Gb);
    break;
  case 0x29:
    op_SUB(ec, op, args_Ev_Gv);
    break;
  case 0x2A:
    op_SUB(ec, op, args_Gb_Eb);
    break;
  case 0x2B:
    op_SUB(ec, op, args_Gv_Ev);
    break;
  case 0x2C:
    op_SUB(ec, op, args_AL_Ib);
    break;
  case 0x2D:
    op_SUB(ec, op, args_eAX_Iv);
    break;
/* Unknown opcode 2E */
  case 0x2F:
    op_DAS(ec, op, args_none);
    break;
  case 0x30:
    op_XOR(ec, op, args_Eb_Gb);
    break;
  case 0x31:
    op_XOR(ec, op, args_Ev_Gv);
    break;
  case 0x32:
    op_XOR(ec, op, args_Gb_Eb);
    break;
  case 0x33:
    op_XOR(ec, op, args_Gv_Ev);
    break;
  case 0x34:
    op_XOR(ec, op, args_AL_Ib);
    break;
  case 0x35:
    op_XOR(ec, op, args_eAX_Iv);
    break;
/* Unknown opcode 36 */
  case 0x37:
    op_AAA(ec, op, args_none);
    break;
  case 0x38:
    op_CMP(ec, op, args_Eb_Gb);
    break;
  case 0x39:
    op_CMP(ec, op, args_Ev_Gv);
    break;
  case 0x3A:
    op_CMP(ec, op, args_Gb_Eb);
    break;
  case 0x3B:
    op_CMP(ec, op, args_Gv_Ev);
    break;
  case 0x3C:
    op_CMP(ec, op, args_AL_Ib);
    break;
  case 0x3D:
    op_CMP(ec, op, args_eAX_Iv);
    break;
/* Unknown opcode 3E */
  case 0x3F:
    op_AAS(ec, op, args_none);
    break;
  case 0x40:
    op_INC(ec, op, args_eAX);
    break;
  case 0x41:
    op_INC(ec, op, args_eCX);
    break;
  case 0x42:
    op_INC(ec, op, args_eDX);
    break;
  case 0x43:
    op_INC(ec, op, args_eBX);
    break;
  case 0x44:
    op_INC(ec, op, args_eSP);
    break;
  case 0x45:
    op_INC(ec, op, args_eBP);
    break;
  case 0x46:
    op_INC(ec, op, args_eSI);
    break;
  case 0x47:
    op_INC(ec, op, args_eDI);
    break;
  case 0x48:
    op_DEC(ec, op, args_eAX);
    break;
  case 0x49:
    op_DEC(ec, op, args_eCX);
    break;
  case 0x4A:
    op_DEC(ec, op, args_eDX);
    break;
  case 0x4B:
    op_DEC(ec, op, args_eBX);
    break;
  case 0x4C:
    op_DEC(ec, op, args_eSP);
    break;
  case 0x4D:
    op_DEC(ec, op, args_eBP);
    break;
  case 0x4E:
    op_DEC(ec, op, args_eSI);
    break;
  case 0x4F:
    op_DEC(ec, op, args_eDI);
    break;
  case 0x50:
    op_PUSH(ec, op, args_eAX);
    break;
  case 0x51:
    op_PUSH(ec, op, args_eCX);
    break;
  case 0x52:
    op_PUSH(ec, op, args_eDX);
    break;
  case 0x53:
    op_PUSH(ec, op, args_eBX);
    break;
  case 0x54:
    op_PUSH(ec, op, args_eSP);
    break;
  case 0x55:
    op_PUSH(ec, op, args_eBP);
    break;
  case 0x56:
    op_PUSH(ec, op, args_eSI);
    break;
  case 0x57:
    op_PUSH(ec, op, args_eDI);
    break;
  case 0x58:
    op_POP(ec, op, args_eAX);
    break;
  case 0x59:
    op_POP(ec, op, args_eCX);
    break;
  case 0x5A:
    op_POP(ec, op, args_eDX);
    break;
  case 0x5B:
    op_POP(ec, op, args_eBX);
    break;
  case 0x5C:
    op_POP(ec, op, args_eSP);
    break;
  case 0x5D:
    op_POP(ec, op, args_eBP);
    break;
  case 0x5E:
    op_POP(ec, op, args_eSI);
    break;
  case 0x5F:
    op_POP(ec, op, args_eDI);
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
  case 0x70:
    op_JO(ec, op, args_Jb);
    break;
  case 0x71:
    op_JNO(ec, op, args_Jb);
    break;
  case 0x72:
    op_JB(ec, op, args_Jb);
    break;
  case 0x73:
    op_JNB(ec, op, args_Jb);
    break;
  case 0x74:
    op_JZ(ec, op, args_Jb);
    break;
  case 0x75:
    op_JNZ(ec, op, args_Jb);
    break;
  case 0x76:
    op_JBE(ec, op, args_Jb);
    break;
  case 0x77:
    op_JA(ec, op, args_Jb);
    break;
  case 0x78:
    op_JS(ec, op, args_Jb);
    break;
  case 0x79:
    op_JNS(ec, op, args_Jb);
    break;
  case 0x7A:
    op_JPE(ec, op, args_Jb);
    break;
  case 0x7B:
    op_JPO(ec, op, args_Jb);
    break;
  case 0x7C:
    op_JL(ec, op, args_Jb);
    break;
  case 0x7D:
    op_JGE(ec, op, args_Jb);
    break;
  case 0x7E:
    op_JLE(ec, op, args_Jb);
    break;
  case 0x7F:
    op_JG(ec, op, args_Jb);
    break;
  case 0x80:
    op_GRP1(ec, op, args_Eb_Ib);
    break;
  case 0x81:
    op_GRP1(ec, op, args_Ev_Iv);
    break;
  case 0x82:
    op_GRP1(ec, op, args_Eb_Ib);
    break;
  case 0x83:
    op_GRP1(ec, op, args_Ev_Ib);
    break;
  case 0x84:
    op_TEST(ec, op, args_Gb_Eb);
    break;
  case 0x85:
    op_TEST(ec, op, args_Gv_Ev);
    break;
  case 0x86:
    op_XCHG(ec, op, args_Gb_Eb);
    break;
  case 0x87:
    op_XCHG(ec, op, args_Gv_Ev);
    break;
  case 0x88:
    op_MOV(ec, op, args_Eb_Gb);
    break;
  case 0x89:
    op_MOV(ec, op, args_Ev_Gv);
    break;
  case 0x8A:
    op_MOV(ec, op, args_Gb_Eb);
    break;
  case 0x8B:
    op_MOV(ec, op, args_Gv_Ev);
    break;
  case 0x8C:
    op_MOV(ec, op, args_Ew_Sw);
    break;
  case 0x8D:
    op_LEA(ec, op, args_Gv_M);
    break;
  case 0x8E:
    op_MOV(ec, op, args_Sw_Ew);
    break;
  case 0x8F:
    op_POP(ec, op, args_Ev);
    break;
  case 0x90:
    op_NOP(ec, op, args_none);
    break;
  case 0x91:
    op_XCHG(ec, op, args_eCXeAX);
    break;
  case 0x92:
    op_XCHG(ec, op, args_eDXeAX);
    break;
  case 0x93:
    op_XCHG(ec, op, args_eBXeAX);
    break;
  case 0x94:
    op_XCHG(ec, op, args_eSPeAX);
    break;
  case 0x95:
    op_XCHG(ec, op, args_eBPeAX);
    break;
  case 0x96:
    op_XCHG(ec, op, args_eSIeAX);
    break;
  case 0x97:
    op_XCHG(ec, op, args_eDIeAX);
    break;
  case 0x98:
    op_CBW(ec, op, args_none);
    break;
  case 0x99:
    op_CWD(ec, op, args_none);
    break;
  case 0x9A:
    op_CALL(ec, op, args_Ap);
    break;
  case 0x9B:
    op_WAIT(ec, op, args_none);
    break;
  case 0x9C:
    op_PUSHF(ec, op, args_none);
    break;
  case 0x9D:
    op_POPF(ec, op, args_none);
    break;
  case 0x9E:
    op_SAHF(ec, op, args_none);
    break;
  case 0x9F:
    op_LAHF(ec, op, args_none);
    break;
  case 0xA0:
    op_MOV(ec, op, args_AL_Ob);
    break;
  case 0xA1:
    op_MOV(ec, op, args_eAX_Ov);
    break;
  case 0xA2:
    op_MOV(ec, op, args_Ob_AL);
    break;
  case 0xA3:
    op_MOV(ec, op, args_Ov_eAX);
    break;
  case 0xA4:
    op_MOVSB(ec, op, args_none);
    break;
  case 0xA5:
    op_MOVSW(ec, op, args_none);
    break;
  case 0xA6:
    op_CMPSB(ec, op, args_none);
    break;
  case 0xA7:
    op_CMPSW(ec, op, args_none);
    break;
  case 0xA8:
    op_TEST(ec, op, args_AL_Ib);
    break;
  case 0xA9:
    op_TEST(ec, op, args_eAX_Iv);
    break;
  case 0xAA:
    op_STOSB(ec, op, args_none);
    break;
  case 0xAB:
    op_STOSW(ec, op, args_none);
    break;
  case 0xAC:
    op_LODSB(ec, op, args_none);
    break;
  case 0xAD:
    op_LODSW(ec, op, args_none);
    break;
  case 0xAE:
    op_SCASB(ec, op, args_none);
    break;
  case 0xAF:
    op_SCASW(ec, op, args_none);
    break;
  case 0xB0:
    op_MOV(ec, op, args_AL_Ib);
    break;
  case 0xB1:
    op_MOV(ec, op, args_CL_Ib);
    break;
  case 0xB2:
    op_MOV(ec, op, args_DL_Ib);
    break;
  case 0xB3:
    op_MOV(ec, op, args_BL_Ib);
    break;
  case 0xB4:
    op_MOV(ec, op, args_AH_Ib);
    break;
  case 0xB5:
    op_MOV(ec, op, args_CH_Ib);
    break;
  case 0xB6:
    op_MOV(ec, op, args_DH_Ib);
    break;
  case 0xB7:
    op_MOV(ec, op, args_BH_Ib);
    break;
  case 0xB8:
    op_MOV(ec, op, args_eAX_Iv);
    break;
  case 0xB9:
    op_MOV(ec, op, args_eCX_Iv);
    break;
  case 0xBA:
    op_MOV(ec, op, args_eDX_Iv);
    break;
  case 0xBB:
    op_MOV(ec, op, args_eBX_Iv);
    break;
  case 0xBC:
    op_MOV(ec, op, args_eSP_Iv);
    break;
  case 0xBD:
    op_MOV(ec, op, args_eBP_Iv);
    break;
  case 0xBE:
    op_MOV(ec, op, args_eSI_Iv);
    break;
  case 0xBF:
    op_MOV(ec, op, args_eDI_Iv);
    break;
/* Unknown opcode C0 */
/* Unknown opcode C1 */
  case 0xC2:
    op_RET(ec, op, args_Iw);
    break;
  case 0xC3:
    op_RET(ec, op, args_none);
    break;
  case 0xC4:
    op_LES(ec, op, args_Gv_Mp);
    break;
  case 0xC5:
    op_LDS(ec, op, args_Gv_Mp);
    break;
  case 0xC6:
    op_MOV(ec, op, args_Eb_Ib);
    break;
  case 0xC7:
    op_MOV(ec, op, args_Ev_Iv);
    break;
/* Unknown opcode C8 */
/* Unknown opcode C9 */
  case 0xCA:
    op_RETF(ec, op, args_Iw);
    break;
  case 0xCB:
    op_RETF(ec, op, args_none);
    break;
  case 0xCC:
    op_INT(ec, op, args_3);
    break;
  case 0xCD:
    op_INT(ec, op, args_Ib);
    break;
  case 0xCE:
    op_INTO(ec, op, args_none);
    break;
  case 0xCF:
    op_IRET(ec, op, args_none);
    break;
  case 0xD0:
    op_GRP2(ec, op, args_Eb_1);
    break;
  case 0xD1:
    op_GRP2(ec, op, args_Ev_1);
    break;
  case 0xD2:
    op_GRP2(ec, op, args_Eb_CL);
    break;
  case 0xD3:
    op_GRP2(ec, op, args_Ev_CL);
    break;
  case 0xD4:
    op_AAM(ec, op, args_I0);
    break;
  case 0xD5:
    op_AAD(ec, op, args_I0);
    break;
/* Unknown opcode D6 */
  case 0xD7:
    op_XLAT(ec, op, args_none);
    break;
/* Unknown opcode D8 */
/* Unknown opcode D9 */
/* Unknown opcode DA */
/* Unknown opcode DB */
/* Unknown opcode DC */
/* Unknown opcode DD */
/* Unknown opcode DE */
/* Unknown opcode DF */
  case 0xE0:
    op_LOOPNZ(ec, op, args_Jb);
    break;
  case 0xE1:
    op_LOOPZ(ec, op, args_Jb);
    break;
  case 0xE2:
    op_LOOP(ec, op, args_Jb);
    break;
  case 0xE3:
    op_JCXZ(ec, op, args_Jb);
    break;
  case 0xE4:
    op_IN(ec, op, args_AL_Ib);
    break;
  case 0xE5:
    op_IN(ec, op, args_eAX_Ib);
    break;
  case 0xE6:
    op_OUT(ec, op, args_Ib_AL);
    break;
  case 0xE7:
    op_OUT(ec, op, args_Ib_eAX);
    break;
  case 0xE8:
    op_CALL(ec, op, args_Jv);
    break;
  case 0xE9:
    op_JMP(ec, op, args_Jv);
    break;
  case 0xEA:
    op_JMP(ec, op, args_Ap);
    break;
  case 0xEB:
    op_JMP(ec, op, args_Jb);
    break;
  case 0xEC:
    op_IN(ec, op, args_AL_DX);
    break;
  case 0xED:
    op_IN(ec, op, args_eAX_DX);
    break;
  case 0xEE:
    op_OUT(ec, op, args_DX_AL);
    break;
  case 0xEF:
    op_OUT(ec, op, args_DX_eAX);
    break;
  case 0xF0:
    op_LOCK(ec, op, args_none);
    break;
/* Unknown opcode F1 */
  case 0xF2:
    op_REPNZ(ec, op, args_none);
    break;
  case 0xF3:
    op_REPZ(ec, op, args_none);
    break;
  case 0xF4:
    op_HLT(ec, op, args_none);
    break;
  case 0xF5:
    op_CMC(ec, op, args_none);
    break;
  case 0xF6:
    op_GRP3a(ec, op, args_Eb);
    break;
  case 0xF7:
    op_GRP3b(ec, op, args_Ev);
    break;
  case 0xF8:
    op_CLC(ec, op, args_none);
    break;
  case 0xF9:
    op_STC(ec, op, args_none);
    break;
  case 0xFA:
    op_CLI(ec, op, args_none);
    break;
  case 0xFB:
    op_STI(ec, op, args_none);
    break;
  case 0xFC:
    op_CLD(ec, op, args_none);
    break;
  case 0xFD:
    op_STD(ec, op, args_none);
    break;
  case 0xFE:
    op_GRP4(ec, op, args_Eb);
    break;
  case 0xFF:
    op_GRP5(ec, op, args_Ev);
    break;
/* Unhandled FF with -1 args */
/* Unhandled FF with -1 args */
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
/* Ignore GRP */
/* Ignore GRP */
/* Unknown opcode GRP5/7 */
  default:
    break;
  }
}
