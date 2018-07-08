#define SPINLOCK_PRU_HEAD    0x480CA800   //head (moved by PRU)
#define SPINLOCK_ARM_TAIL    0x480CA804   //tail (moved by ARM)
#define SPINLOCK_STATS       0x480CA808   //stats

#define SHBUF0_START    0x90000000
#define SHBUF0_SIZE     0x4000
#define SHBUF0_END      SHBUF0_START+SHBUF0_SIZE

#define SHBUF0_CTRL_BLOCK     (SHBUF0_START+SHBUF0_SIZE)
#define SHBUF0_HEAD_OFFSET    (SHBUF0_CTRL_BLOCK)           //head (moved by PRU)
#define SHBUF0_TAIL_OFFSET    (SHBUF0_HEAD_OFFSET + 4)      //tail (moved by ARM)
