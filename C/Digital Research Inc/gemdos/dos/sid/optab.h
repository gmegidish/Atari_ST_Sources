/* struct for optab */
struct optbl {
    WORD inmsk;
    WORD invalu;
    WORD infmt;
    BYTE *innam;
};
 
#define MAXFMT  28
#define OPENT 4   /* # words per line in optab */
 
struct optbl optab[] = {
    0xffff, 0x023c, 3,      "andi.b",
    0xffff, 0x027c, 3,      "andi.w",
    0xffff, 0x0a3c, 3,      "eori.b",
    0xffff, 0x0a7c, 3,      "eori.w",
    0xffff, 0x4afa, 0,      "illegal",
    0xffff, 0x4afb, 0,      "illegal",
    0xffff, 0x4afc, 0,      "illegal",
    0xffff, 0x4e71, 0,      "nop",
    0xffff, 0x003c, 3,      "ori.b",
    0xffff, 0x007c, 3,      "ori.w",
    0xffff, 0x4e70, 0,      "reset",
    0xffff, 0x4e74, 21,     "rtd",
    0xffff, 0x4e73, 0,      "rte",
    0xffff, 0x4e77, 0,      "rtr",
    0xffff, 0x4e75, 0,      "rts",
    0xffff, 0x4e72, 21,     "stop",
    0xffff, 0x4e76, 0,      "trapv",
    0xfffe, 0x4e7a, 24,     "movec",
    0xfff8, 0x50c8, 12,     "dbt",
    0xfff8, 0x51c8, 12,     "dbf",
    0xfff8, 0x52c8, 12,     "dbhi",
    0xfff8, 0x53c8, 12,     "dbls",
    0xfff8, 0x54c8, 12,     "dbcc",
    0xfff8, 0x55c8, 12,     "dbcs",
    0xfff8, 0x56c8, 12,     "dbne",
    0xfff8, 0x57c8, 12,     "dbeq",
    0xfff8, 0x58c8, 12,     "dbvc",
    0xfff8, 0x59c8, 12,     "dbvs",
    0xfff8, 0x5ac8, 12,     "dbpl",
    0xfff8, 0x5bc8, 12,     "dbmi",
    0xfff8, 0x5cc8, 12,     "dbge",
    0xfff8, 0x5dc8, 12,     "dblt",
    0xfff8, 0x5ec8, 12,     "dbgt",
    0xfff8, 0x5fc8, 12,     "dble",
    0xfff8, 0x4880, 14,     "ext.w",
    0xfff8, 0x48c0, 14,     "ext.l",
    0xfff8, 0x4e50, 15,     "link",
    0xfff8, 0x4e60, 17,     "move.l",	/* move usp */
    0xfff8, 0x4e68, 17,     "move.l",
    0xfff8, 0x4840, 22,     "swap",
    0xfff8, 0x4e58, 22,     "unlk",
    0xfff0, 0x4e40, 23,     "trap",
    0xffc0, 0x0600, 3,      "addi.b",
    0xffc0, 0x0640, 3,      "addi.w",
    0xffc0, 0x0680, 3,      "addi.l",
    0xffc0, 0x0200, 3,      "andi.b",
    0xffc0, 0x0240, 3,      "andi.w",
    0xffc0, 0x0280, 3,      "andi.l",
    0xffc0, 0xe1c0, 7,      "asl",
    0xffc0, 0xe0c0, 7,      "asr",
    0xffc0, 0x0840, 10,     "bchg",
    0xffc0, 0x0880, 10,     "bclr",
    0xffc0, 0x08c0, 10,     "bset",
    0xffc0, 0x0800, 10,     "btst",
    0xffc0, 0x4200, 7,      "clr.b",
    0xffc0, 0x4240, 7,      "clr.w",
    0xffc0, 0x4280, 7,      "clr.l",
    0xffc0, 0x0c00, 3,      "cmpi.b",
    0xffc0, 0x0c40, 3,      "cmpi.w",
    0xffc0, 0x0c80, 3,      "cmpi.l",
    0xffc0, 0x0a00, 3,      "eori.b",
    0xffc0, 0x0a40, 3,      "eori.w",
    0xffc0, 0x0a80, 3,      "eori.l",
    0xffc0, 0x4ec0, 7,      "jmp",
    0xffc0, 0x4e80, 7,      "jsr",
    0xffc0, 0xe3c0, 7,      "lsl",
    0xffc0, 0xe2c0, 7,      "lsr",
    0xffc0, 0x42c0, 5,      "move.w",
    0xffc0, 0x44c0, 5,      "move.w",
    0xffc0, 0x46c0, 5,      "move.w",
    0xffc0, 0x40c0, 5,      "move.w",
    0xffc0, 0x4c80, 18,     "movem.w",
    0xffc0, 0x4cc0, 18,     "movem.l",
    0xffc0, 0x4880, 18,     "movem.w",
    0xffc0, 0x48c0, 18,     "movem.l",
    0xffc0, 0x0e00, 25,     "moves.b",
    0xffc0, 0x0e40, 25,     "moves.w",
    0xffc0, 0x0e80, 25,     "moves.l",
    0xffc0, 0x4800, 7,      "nbcd",
    0xffc0, 0x4400, 7,      "neg.b",
    0xffc0, 0x4440, 7,      "neg.w",
    0xffc0, 0x4480, 7,      "neg.l",
    0xffc0, 0x4000, 7,      "negx.b",
    0xffc0, 0x4040, 7,      "negx.w",
    0xffc0, 0x4080, 7,      "negx.l",
    0xffc0, 0x4600, 7,      "not.b",
    0xffc0, 0x4640, 7,      "not.w",
    0xffc0, 0x4680, 7,      "not.l",
    0xffc0, 0x0000, 3,      "ori.b",
    0xffc0, 0x0040, 3,      "ori.w",
    0xffc0, 0x0080, 3,      "ori.l",
    0xffc0, 0x4840, 7,      "pea",
    0xffc0, 0xe7c0, 7,      "rol",
    0xffc0, 0xe6c0, 7,      "ror",	   /* rotate memory */
    0xffc0, 0xe5c0, 7,      "roxl",
    0xffc0, 0xe4c0, 7,      "roxr",
    0xffc0, 0x50c0, 7,      "st",
    0xffc0, 0x51c0, 7,      "sf",
    0xffc0, 0x52c0, 7,      "shi",
    0xffc0, 0x53c0, 7,      "sls",
    0xffc0, 0x54c0, 7,      "scc",
    0xffc0, 0x55c0, 7,      "scs",
    0xffc0, 0x56c0, 7,      "sne",
    0xffc0, 0x57c0, 7,      "seq",
    0xffc0, 0x58c0, 7,      "svc",
    0xffc0, 0x59c0, 7,      "svs",
    0xffc0, 0x5ac0, 7,      "spl",
    0xffc0, 0x5bc0, 7,      "smi",
    0xffc0, 0x5cc0, 7,      "sge",
    0xffc0, 0x5dc0, 7,      "slt",
    0xffc0, 0x5ec0, 7,      "sgt",
    0xffc0, 0x5fc0, 7,      "sle",
    0xffc0, 0x0400, 3,      "subi.b",
    0xffc0, 0x0440, 3,      "subi.w",
    0xffc0, 0x0480, 3,      "subi.l",
    0xffc0, 0x4ac0, 7,      "tas.b",
    0xffc0, 0x4a00, 7,      "tst.b",
    0xffc0, 0x4a40, 7,      "tst.w",
    0xffc0, 0x4a80, 7,      "tst.l",
    0xff00, 0x6200, 8,      "bhi",
    0xff00, 0x6300, 8,      "bls",
    0xff00, 0x6400, 8,      "bcc",
    0xff00, 0x6500, 8,      "bcs",
    0xff00, 0x6600, 8,      "bne",
    0xff00, 0x6700, 8,      "beq",
    0xff00, 0x6800, 8,      "bvc",
    0xff00, 0x6900, 8,      "bvs",
    0xff00, 0x6a00, 8,      "bpl",
    0xff00, 0x6b00, 8,      "bmi",
    0xff00, 0x6c00, 8,      "bge",
    0xff00, 0x6d00, 8,      "blt",
    0xff00, 0x6e00, 8,      "bgt",
    0xff00, 0x6f00, 8,      "ble",
    0xff00, 0x6000, 8,      "bra",
    0xff00, 0x6100, 8,      "bsr",
    0xf1f8, 0xc100, 1,      "abcd",
    0xf1f8, 0xc108, 1,      "abcd",
    0xf1f8, 0xd100, 1,      "addx.b",
    0xf1f8, 0xd140, 1,      "addx.w",
    0xf1f8, 0xd180, 1,      "addx.l",
    0xf1f8, 0xd108, 1,      "addx.b",
    0xf1f8, 0xd148, 1,      "addx.w",
    0xf1f8, 0xd188, 1,      "addx.l",
    0xf1f8, 0xc140, 13,     "exg",
    0xf1f8, 0xc148, 13,     "exg",
    0xf1f8, 0xc188, 13,     "exg",
    0xf1f8, 0xe100, 6,      "asl.b",
    0xf1f8, 0xe140, 6,      "asl.w",
    0xf1f8, 0xe180, 6,      "asl.l",
    0xf1f8, 0xe120, 6,      "asl.b",
    0xf1f8, 0xe160, 6,      "asl.w",
    0xf1f8, 0xe1a0, 6,      "asl.l",
    0xf1f8, 0xe000, 6,      "asr.b",
    0xf1f8, 0xe040, 6,      "asr.w",
    0xf1f8, 0xe080, 6,      "asr.l",
    0xf1f8, 0xe020, 6,      "asr.b",
    0xf1f8, 0xe060, 6,      "asr.w",
    0xf1f8, 0xe0a0, 6,      "asr.l",
    0xf1f8, 0xb108, 11,     "cmpm.b",
    0xf1f8, 0xb148, 11,     "cmpm.w",
    0xf1f8, 0xb188, 11,     "cmpm.l",
    0xf1f8, 0xe108, 6,      "lsl.b",
    0xf1f8, 0xe148, 6,      "lsl.w",
    0xf1f8, 0xe188, 6,      "lsl.l",
    0xf1f8, 0xe128, 6,      "lsl.b",
    0xf1f8, 0xe168, 6,      "lsl.w",
    0xf1f8, 0xe1a8, 6,      "lsl.l",
    0xf1f8, 0xe008, 6,      "lsr.b",
    0xf1f8, 0xe048, 6,      "lsr.w",
    0xf1f8, 0xe088, 6,      "lsr.l",
    0xf1f8, 0xe028, 6,      "lsr.b",
    0xf1f8, 0xe068, 6,      "lsr.w",
    0xf1f8, 0xe0a8, 6,      "lsr.l",
    0xf1f8, 0x0108, 19,     "movep.w",
    0xf1f8, 0x0148, 19,     "movep.l",
    0xf1f8, 0x0188, 19,     "movep.w",
    0xf1f8, 0x01c8, 19,     "movep.l",
    0xf1f8, 0xe118, 6,      "rol.b",	   /* rotate register */
    0xf1f8, 0xe158, 6,      "rol.w",
    0xf1f8, 0xe198, 6,      "rol.l",
    0xf1f8, 0xe138, 6,      "rol.b",
    0xf1f8, 0xe178, 6,      "rol.w",
    0xf1f8, 0xe1b8, 6,      "rol.l",
    0xf1f8, 0xe018, 6,      "ror.b",
    0xf1f8, 0xe058, 6,      "ror.w",
    0xf1f8, 0xe098, 6,      "ror.l",
    0xf1f8, 0xe038, 6,      "ror.b",
    0xf1f8, 0xe078, 6,      "ror.w",
    0xf1f8, 0xe0b8, 6,      "ror.l",
    0xf1f8, 0xe110, 6,      "roxl.b",
    0xf1f8, 0xe150, 6,      "roxl.w",
    0xf1f8, 0xe190, 6,      "roxl.l",
    0xf1f8, 0xe130, 6,      "roxl.b",
    0xf1f8, 0xe170, 6,      "roxl.w",
    0xf1f8, 0xe1b0, 6,      "roxl.l",
    0xf1f8, 0xe010, 6,      "roxr.b",
    0xf1f8, 0xe050, 6,      "roxr.w",
    0xf1f8, 0xe090, 6,      "roxr.l",
    0xf1f8, 0xe030, 6,      "roxr.b",
    0xf1f8, 0xe070, 6,      "roxr.w",
    0xf1f8, 0xe0b0, 6,      "roxr.l",
    0xf1f8, 0x8100, 1,      "sbcd",
    0xf1f8, 0x8108, 1,      "sbcd",
    0xf1f8, 0x9100, 1,      "subx.b",
    0xf1f8, 0x9140, 1,      "subx.w",
    0xf1f8, 0x9180, 1,      "subx.l",
    0xf1f8, 0x9108, 1,      "subx.b",
    0xf1f8, 0x9148, 1,      "subx.w",
    0xf1f8, 0x9188, 1,      "subx.l",
    0xf1c0, 0xd000, 2,      "add.b",
    0xf1c0, 0xd040, 2,      "add.w",
    0xf1c0, 0xd080, 2,      "add.l",
    0xf1c0, 0xd100, 2,      "add.b",
    0xf1c0, 0xd140, 2,      "add.w",
    0xf1c0, 0xd180, 2,      "add.l",
    0xf1c0, 0xd0c0, 2,      "adda.w",
    0xf1c0, 0xd1c0, 2,      "adda.l",
    0xf1c0, 0x5000, 4,      "addq.b",
    0xf1c0, 0x5040, 4,      "addq.w",
    0xf1c0, 0x5080, 4,      "addq.l",
    0xf1c0, 0xc000, 2,      "and.b",
    0xf1c0, 0xc040, 2,      "and.w",
    0xf1c0, 0xc080, 2,      "and.l",
    0xf1c0, 0xc100, 2,      "and.b",
    0xf1c0, 0xc140, 2,      "and.w",
    0xf1c0, 0xc180, 2,      "and.l",
    0xf1c0, 0x0140, 10,     "bchg",
    0xf1c0, 0x0180, 10,     "bclr",
    0xf1c0, 0x01c0, 10,     "bset",
    0xf1c0, 0x0100, 10,     "btst",	/* fix to Belton's code */
    0xf1c0, 0x4180, 9,      "chk",
    0xf1c0, 0xb000, 2,      "cmp.b",
    0xf1c0, 0xb040, 2,      "cmp.w",
    0xf1c0, 0xb080, 2,      "cmp.l",
    0xf1c0, 0xb0c0, 2,      "cmpa.w",
    0xf1c0, 0xb1c0, 2,      "cmpa.l",
    0xf1c0, 0x81c0, 9,      "divs",
    0xf1c0, 0x80c0, 9,      "divu",
    0xf1c0, 0xb100, 2,      "eor.b",
    0xf1c0, 0xb140, 2,      "eor.w",
    0xf1c0, 0xb180, 2,      "eor.l",
    0xf1c0, 0x41c0, 2,      "lea",
    0xf1c0, 0x3040, 16,     "movea.w",
    0xf1c0, 0x2040, 16,     "movea.l",
    0xf1c0, 0xc1c0, 9,      "muls",
    0xf1c0, 0xc0c0, 9,      "mulu",
    0xf1c0, 0x8000, 2,      "or.b",
    0xf1c0, 0x8040, 2,      "or.w",
    0xf1c0, 0x8080, 2,      "or.l",
    0xf1c0, 0x8100, 2,      "or.b",
    0xf1c0, 0x8140, 2,      "or.w",
    0xf1c0, 0x8180, 2,      "or.l",
    0xf1c0, 0x9000, 2,      "sub.b",
    0xf1c0, 0x9040, 2,      "sub.w",
    0xf1c0, 0x9080, 2,      "sub.l",
    0xf1c0, 0x9100, 2,      "sub.b",
    0xf1c0, 0x9140, 2,      "sub.w",
    0xf1c0, 0x9180, 2,      "sub.l",
    0xf1c0, 0x90c0, 2,      "suba.w",
    0xf1c0, 0x91c0, 2,      "suba.l",
    0xf1c0, 0x5100, 4,      "subq.b",
    0xf1c0, 0x5140, 4,      "subq.w",
    0xf1c0, 0x5180, 4,      "subq.l",
    0xf100, 0x7000, 20,     "moveq.l",
    0xf000, 0x1000, 16,     "move.b",
    0xf000, 0x3000, 16,     "move.w",
    0xf000, 0x2000, 16,     "move.l",
    0x0000, 0x0000, 0,      "*unknown instruction*"
};

