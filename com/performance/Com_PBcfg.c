/* Com_PBcfg.c */
#include "Os.h"
#include "Com.h"
#include "Com_Cbk.h"
#include "Rte_Cbk.h"

/*
 * ComConfig_0
 */

/* IPDU_INIBプロトタイプ宣言 : <送受信>_ipdu_inib_list_<ComConfig> */
static const IPDU_INIB tx_ipdu_inib_list_ComConfig_0[12];	/* ComIPdu_0, ComIPdu_1, ComIPdu_2, ComIPdu_3, ComIPdu_4, ComIPdu_5, ComIPdu_6, ComIPdu_7, ComIPdu_8, ComIPdu_9, ComIPdu_10, ComIPdu_11 */

/* IPDUバッファ：ipdu_buffer_<ComConfig>_<ComIPdu> */
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_0[15];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_1[15];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_2[16];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_3[16];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_4[16];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_5[16];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_6[25];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_7[25];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_8[18];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_9[16];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_10[16];
static uint8 ipdu_buffer_ComConfig_0_ComIPdu_11[10];

/* シグナルバッファ：signal_buffer_<ComConfig>_<ComSignal> */
static boolean signal_buffer_ComConfig_0_ComSignal_35;
static uint8   signal_buffer_ComConfig_0_ComSignal_83;

/* フィルタバッファ: filter_buffer_<ComConfig>_<ComSignal> */
static sint32 filter_buffer_ComConfig_0_ComSignal_36;
static uint8 filter_buffer_ComConfig_0_ComSignal_37;
static uint16 filter_buffer_ComConfig_0_ComSignal_38;
static uint16 filter_buffer_ComConfig_0_ComSignal_39;
static boolean filter_buffer_ComConfig_0_ComSignal_40;
static uint16 filter_buffer_ComConfig_0_ComSignal_41;
static sint16 filter_buffer_ComConfig_0_ComSignal_42;
static uint32 filter_buffer_ComConfig_0_ComSignal_43;
static sint8 filter_buffer_ComConfig_0_ComSignal_44;

/* シグナル管理ブロック：<送受信>_signal_cb_<ComConfig>_<ComSignal> */
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_0;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_1;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_2;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_4;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_5;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_6;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_8;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_9;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_10;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_11;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_13;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_14;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_15;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_17;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_18;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_19;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_20;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_21;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_22;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_23;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_27;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_28;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_29;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_30;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_31;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_32;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_36;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_37;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_38;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_39;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_40;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_41;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_42;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_43;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_44;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_45;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_46;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_47;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_48;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_49;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_50;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_51;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_52;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_53;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_54;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_55;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_56;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_57;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_58;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_59;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_60;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_61;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_62;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_63;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_64;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_74;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_66;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_67;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_68;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_69;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_70;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_71;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_72;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_73;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_65;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_77;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_78;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_82;
static TX_SIGNAL_CB tx_signal_cb_ComConfig_0_ComSignal_83;

/* シグナル無効値：signal_invalid_value_<ComConfig>_<ComSignal> */
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_0 = -1;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_1 = 42;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_2 = FALSE;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_3 = 265080016;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_4 = 238;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_5 = 0;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_6 = 255;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_7 = 1450;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_8 = 209715;
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_9 = -1;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_10 = 42;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_11 = FALSE;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_12 = 265080016;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_13 = 238;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_14 = 0;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_15 = 255;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_16 = 1450;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_17 = 209715;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_18 = 8191;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_19 = 273;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_20 = 78643;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_21 = -888;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_22 = 0;
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_23 = -128;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_24 = 256;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_25 = 61166;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_26 = FALSE;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_27 = 8191;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_28 = 273;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_29 = 78643;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_30 = -888;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_31 = 0;
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_32 = -128;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_33 = 256;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_34 = 61166;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_35 = FALSE;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_36 = 62;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_37 = 7;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_38 = 0;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_39 = 1228;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_40 = TRUE;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_41 = 1365;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_42 = 0;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_43 = 42;
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_44 = 1;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_45 = 10;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_46 = 4369;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_47 = 489335;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_48 = -1;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_49 = 15;
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_50 = 1;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_51 = -256;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_52 = 119;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_53[3] = {0x41, 0x54, 0x4B};
static const boolean signal_invalid_value_ComConfig_0_ComSignal_54 = FALSE;
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_55 = 1;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_56 = 47;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_57 = -1;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_58 = 4369;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_59 = 1092;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_60 = 1023;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_61 = 0;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_62 = 1;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_63 = TRUE;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_64[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x54, 0x4B};
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_74[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x54, 0x4B};
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_66 = 47;
static const sint32  signal_invalid_value_ComConfig_0_ComSignal_67 = -31;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_68 = 4369;
static const sint16  signal_invalid_value_ComConfig_0_ComSignal_69 = 1092;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_70 = 1023;
static const uint16  signal_invalid_value_ComConfig_0_ComSignal_71 = 0;
static const uint32  signal_invalid_value_ComConfig_0_ComSignal_72 = 1;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_73 = TRUE;
static const sint8   signal_invalid_value_ComConfig_0_ComSignal_65 = 1;
static const float32  signal_invalid_value_ComConfig_0_ComSignal_79 = 0.0;
static const float64  signal_invalid_value_ComConfig_0_ComSignal_80 = 1.0;
static const boolean signal_invalid_value_ComConfig_0_ComSignal_81 = TRUE;
static const uint8   signal_invalid_value_ComConfig_0_ComSignal_83 = 5;

/* シグナル初期値：signal_init_value_<ComConfig>_<ComSignal> */
static const sint8   signal_init_value_ComConfig_0_ComSignal_0 = 0;
static const sint16  signal_init_value_ComConfig_0_ComSignal_1 = -43;
static const boolean signal_init_value_ComConfig_0_ComSignal_2 = TRUE;
static const uint32  signal_init_value_ComConfig_0_ComSignal_3 = 178956976;
static const uint32  signal_init_value_ComConfig_0_ComSignal_4 = 255;
static const uint8   signal_init_value_ComConfig_0_ComSignal_5 = 1;
static const uint16  signal_init_value_ComConfig_0_ComSignal_6 = 0;
static const uint16  signal_init_value_ComConfig_0_ComSignal_7 = 1911;
static const sint32  signal_init_value_ComConfig_0_ComSignal_8 = -209716;
static const sint8   signal_init_value_ComConfig_0_ComSignal_9 = 0;
static const sint16  signal_init_value_ComConfig_0_ComSignal_10 = -43;
static const boolean signal_init_value_ComConfig_0_ComSignal_11 = TRUE;
static const uint32  signal_init_value_ComConfig_0_ComSignal_12 = 178956976;
static const uint32  signal_init_value_ComConfig_0_ComSignal_13 = 255;
static const uint8   signal_init_value_ComConfig_0_ComSignal_14 = 1;
static const uint16  signal_init_value_ComConfig_0_ComSignal_15 = 0;
static const uint16  signal_init_value_ComConfig_0_ComSignal_16 = 1911;
static const sint32  signal_init_value_ComConfig_0_ComSignal_17 = -209716;
static const uint16  signal_init_value_ComConfig_0_ComSignal_18 = 255;
static const sint16  signal_init_value_ComConfig_0_ComSignal_19 = 0;
static const uint32  signal_init_value_ComConfig_0_ComSignal_20 = 511;
static const sint32  signal_init_value_ComConfig_0_ComSignal_21 = 273;
static const uint8   signal_init_value_ComConfig_0_ComSignal_22 = 10;
static const sint8   signal_init_value_ComConfig_0_ComSignal_23 = -52;
static const uint16  signal_init_value_ComConfig_0_ComSignal_24 = 5;
static const uint32  signal_init_value_ComConfig_0_ComSignal_25 = 375;
static const boolean signal_init_value_ComConfig_0_ComSignal_26 = TRUE;
static const uint16  signal_init_value_ComConfig_0_ComSignal_27 = 255;
static const sint16  signal_init_value_ComConfig_0_ComSignal_28 = 0;
static const uint32  signal_init_value_ComConfig_0_ComSignal_29 = 511;
static const sint32  signal_init_value_ComConfig_0_ComSignal_30 = 273;
static const uint8   signal_init_value_ComConfig_0_ComSignal_31 = 10;
static const sint8   signal_init_value_ComConfig_0_ComSignal_32 = -52;
static const uint16  signal_init_value_ComConfig_0_ComSignal_33 = 5;
static const uint32  signal_init_value_ComConfig_0_ComSignal_34 = 375;
static const boolean signal_init_value_ComConfig_0_ComSignal_35 = TRUE;
static const sint32  signal_init_value_ComConfig_0_ComSignal_36 = -16384;
static const uint8   signal_init_value_ComConfig_0_ComSignal_37 = 1;
static const uint16  signal_init_value_ComConfig_0_ComSignal_38 = 4095;
static const uint16  signal_init_value_ComConfig_0_ComSignal_39 = 0;
static const boolean signal_init_value_ComConfig_0_ComSignal_40 = FALSE;
static const uint16  signal_init_value_ComConfig_0_ComSignal_41 = 682;
static const sint16  signal_init_value_ComConfig_0_ComSignal_42 = 32;
static const uint32  signal_init_value_ComConfig_0_ComSignal_43 = 64;
static const sint8   signal_init_value_ComConfig_0_ComSignal_44 = 0;
static const uint8   signal_init_value_ComConfig_0_ComSignal_45 = 11;
static const uint16  signal_init_value_ComConfig_0_ComSignal_46 = 8191;
static const uint32  signal_init_value_ComConfig_0_ComSignal_47 = 279620;
static const sint16  signal_init_value_ComConfig_0_ComSignal_48 = -64;
static const uint16  signal_init_value_ComConfig_0_ComSignal_49 = 1;
static const sint8   signal_init_value_ComConfig_0_ComSignal_50 = -1;
static const sint32  signal_init_value_ComConfig_0_ComSignal_51 = 0;
static const uint32  signal_init_value_ComConfig_0_ComSignal_52 = 63;
static const uint8   signal_init_value_ComConfig_0_ComSignal_53[3] = {0x41, 0x54, 0x4B};
static const boolean signal_init_value_ComConfig_0_ComSignal_54 = TRUE;
static const sint8   signal_init_value_ComConfig_0_ComSignal_55 = -1;
static const uint8   signal_init_value_ComConfig_0_ComSignal_56 = 3;
static const sint32  signal_init_value_ComConfig_0_ComSignal_57 = -4;
static const uint32  signal_init_value_ComConfig_0_ComSignal_58 = 13107;
static const sint16  signal_init_value_ComConfig_0_ComSignal_59 = -1912;
static const uint16  signal_init_value_ComConfig_0_ComSignal_60 = 160;
static const uint16  signal_init_value_ComConfig_0_ComSignal_61 = 4352;
static const uint32  signal_init_value_ComConfig_0_ComSignal_62 = 65535;
static const boolean signal_init_value_ComConfig_0_ComSignal_63 = FALSE;
static const uint8   signal_init_value_ComConfig_0_ComSignal_64[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x54, 0x4B};
static const uint8   signal_init_value_ComConfig_0_ComSignal_74[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x54, 0x4B};
static const uint8   signal_init_value_ComConfig_0_ComSignal_66 = 3;
static const sint32  signal_init_value_ComConfig_0_ComSignal_67 = 30;
static const uint32  signal_init_value_ComConfig_0_ComSignal_68 = 13107;
static const sint16  signal_init_value_ComConfig_0_ComSignal_69 = -1912;
static const uint16  signal_init_value_ComConfig_0_ComSignal_70 = 160;
static const uint16  signal_init_value_ComConfig_0_ComSignal_71 = 4352;
static const uint32  signal_init_value_ComConfig_0_ComSignal_72 = 65535;
static const boolean signal_init_value_ComConfig_0_ComSignal_73 = FALSE;
static const sint8   signal_init_value_ComConfig_0_ComSignal_65 = -1;
static const uint8   signal_init_value_ComConfig_0_ComSignal_75[1] = {65};
static const uint8   signal_init_value_ComConfig_0_ComSignal_76 = 1;
static const boolean signal_init_value_ComConfig_0_ComSignal_77 = TRUE;
static const boolean signal_init_value_ComConfig_0_ComSignal_78 = FALSE;
static const float32  signal_init_value_ComConfig_0_ComSignal_79 = 4352.0;
static const float64  signal_init_value_ComConfig_0_ComSignal_80 = 65535.0;
static const boolean signal_init_value_ComConfig_0_ComSignal_81 = FALSE;
static const uint8   signal_init_value_ComConfig_0_ComSignal_82[1] = {65};
static const uint8   signal_init_value_ComConfig_0_ComSignal_83 = 1;

/* OCCURRENCEカウンタ : occur_<ComConfig>_<ComSignal> */
static uint32 occur_ComConfig_0_ComSignal_45;
static uint32 occur_ComConfig_0_ComSignal_46;
static uint32 occur_ComConfig_0_ComSignal_47;
static uint32 occur_ComConfig_0_ComSignal_48;
static uint32 occur_ComConfig_0_ComSignal_49;
static uint32 occur_ComConfig_0_ComSignal_50;
static uint32 occur_ComConfig_0_ComSignal_51;
static uint32 occur_ComConfig_0_ComSignal_52;
static uint32 occur_ComConfig_0_ComSignal_54;

/* フィルタ初期化ブロック : filter_inib_<ComConfig>_<ComSignal> */
static const FILTER_SINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_0 = {
	27,	/* ComFilterMask */
	28	/* ComFilterX */
};
static const FILTER_SINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_1 = {
	28,	/* ComFilterMask */
	48	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_2 = {
	1,	/* ComFilterMask */
	0	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_4 = {
	60,	/* ComFilterMask */
	1	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_5 = {
	15,	/* ComFilterMask */
	4	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_6 = {
	195,	/* ComFilterMask */
	128	/* ComFilterX */
};
static const FILTER_SINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_8 = {
	209715,	/* ComFilterMask */
	209715	/* ComFilterX */
};
static const FILTER_SINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_9 = {
	27,	/* ComFilterMask */
	16	/* ComFilterX */
};
static const FILTER_SINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_10 = {
	28,	/* ComFilterMask */
	12	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_11 = {
	1,	/* ComFilterMask */
	1	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_13 = {
	60,	/* ComFilterMask */
	128	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_14 = {
	15,	/* ComFilterMask */
	3	/* ComFilterX */
};
static const FILTER_UINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_15 = {
	195,	/* ComFilterMask */
	129	/* ComFilterX */
};
static const FILTER_SINT_MASKED_INIB filter_inib_ComConfig_0_ComSignal_17 = {
	209715,	/* ComFilterMask */
	139810	/* ComFilterX */
};
static const FILTER_UINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_18 = {
	8191,	/* ComFilterMax */
	4096	/* ComFilterMin */
};
static const FILTER_SINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_19 = {
	511,	/* ComFilterMax */
	256	/* ComFilterMin */
};
static const FILTER_UINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_20 = {
	30583,	/* ComFilterMax */
	4369	/* ComFilterMin */
};
static const FILTER_SINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_21 = {
	768,	/* ComFilterMax */
	512	/* ComFilterMin */
};
static const FILTER_UINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_22 = {
	10,	/* ComFilterMax */
	5	/* ComFilterMin */
};
static const FILTER_SINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_23 = {
	175,	/* ComFilterMax */
	170	/* ComFilterMin */
};
static const FILTER_UINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_27 = {
	8191,	/* ComFilterMax */
	4096	/* ComFilterMin */
};
static const FILTER_SINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_28 = {
	511,	/* ComFilterMax */
	256	/* ComFilterMin */
};
static const FILTER_UINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_29 = {
	30583,	/* ComFilterMax */
	4369	/* ComFilterMin */
};
static const FILTER_SINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_30 = {
	768,	/* ComFilterMax */
	512	/* ComFilterMin */
};
static const FILTER_UINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_31 = {
	10,	/* ComFilterMax */
	5	/* ComFilterMin */
};
static const FILTER_SINT_NEW_IS_INIB filter_inib_ComConfig_0_ComSignal_32 = {
	175,	/* ComFilterMax */
	170	/* ComFilterMin */
};
static const FILTER_SINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_36 = {
	8191,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_36	/* p_filter_buffer */
};
static const FILTER_UINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_37 = {
	3,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_37	/* p_filter_buffer */
};
static const FILTER_UINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_38 = {
	240,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_38	/* p_filter_buffer */
};
static const FILTER_UINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_39 = {
	255,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_39	/* p_filter_buffer */
};
static const FILTER_UINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_40 = {
	1,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_40	/* p_filter_buffer */
};
static const FILTER_UINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_41 = {
	783,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_41	/* p_filter_buffer */
};
static const FILTER_SINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_42 = {
	1024,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_42	/* p_filter_buffer */
};
static const FILTER_UINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_43 = {
	63,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_43	/* p_filter_buffer */
};
static const FILTER_SINT_MASKED_OLD_INIB filter_inib_ComConfig_0_ComSignal_44 = {
	62,	/* ComFilterMask */
	(void *)&filter_buffer_ComConfig_0_ComSignal_44	/* p_filter_buffer */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_45 = {
	4U,	/* ComFilterOffset */
	5U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_45	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_46 = {
	5U,	/* ComFilterOffset */
	10U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_46	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_47 = {
	6U,	/* ComFilterOffset */
	7U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_47	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_48 = {
	4U,	/* ComFilterOffset */
	5U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_48	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_49 = {
	3U,	/* ComFilterOffset */
	4U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_49	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_50 = {
	4U,	/* ComFilterOffset */
	6U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_50	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_51 = {
	5U,	/* ComFilterOffset */
	8U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_51	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_52 = {
	4U,	/* ComFilterOffset */
	8U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_52	/* p_occur */
};
static const FILTER_ONE_EVERY_N_INIB filter_inib_ComConfig_0_ComSignal_54 = {
	5U,	/* ComFilterOffset */
	7U,	/* ComFilterPeriod */
	&occur_ComConfig_0_ComSignal_54	/* p_occur */
};

/* シグナル初期化ブロックテーブル：signal_inib_table_<ComConfig> */
static const SIGNAL_INIB signal_inib_table_ComConfig_0[84] = {
	/* ComSignal_0 */
	{
		5U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		2U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn0,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn0,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn0,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_0,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_0,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_MASKED_NEW_DIFFERS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_0,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_0,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_1 */
	{
		7U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		8U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		15U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn1,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn1,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn1,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_1,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_1,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_MASKED_NEW_DIFFERS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_1,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_1,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_2 */
	{
		1U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		18U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		16U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn2,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn2,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn2,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_2,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_2,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_MASKED_NEW_DIFFERS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_2,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_2,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_3 */
	{
		28U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		50U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		31U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn3,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn3,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn3,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_3,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_3,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_4 */
	{
		8U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		56U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		48U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn4,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn4,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn4,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_4,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_4,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_MASKED_NEW_DIFFERS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_4,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_4,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_5 */
	{
		5U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		66U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		71U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn5,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn5,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn5,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_5,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_5,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_MASKED_NEW_DIFFERS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_5,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_5,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_6 */
	{
		8U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		72U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		83U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn6,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn6,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn6,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_6,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_6,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_MASKED_NEW_DIFFERS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_6,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_6,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_7 */
	{
		11U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		85U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		96U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn7,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn7,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn7,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_7,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_7,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_8 */
	{
		20U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		98U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		119U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn8,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn8,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn8,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_8,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_8,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[0],	/* ComIPdu_0 */
		COM_MASKED_NEW_DIFFERS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_8,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_8,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_9 */
	{
		5U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		2U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn9,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn9,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn9,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_9,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_9,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_MASKED_NEW_EQUALS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_9,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_9,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_10 */
	{
		7U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		8U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		15U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn10,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn10,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn10,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_10,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_10,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_MASKED_NEW_EQUALS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_10,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_10,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_11 */
	{
		1U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		18U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		16U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn11,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn11,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn11,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_11,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_11,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_MASKED_NEW_EQUALS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_11,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_11,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_12 */
	{
		28U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		50U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		31U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn12,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn12,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn12,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_12,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_12,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_13 */
	{
		8U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		56U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		48U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn13,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn13,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn13,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_13,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_13,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_MASKED_NEW_EQUALS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_13,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_13,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_14 */
	{
		5U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		66U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		71U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn14,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn14,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn14,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_14,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_14,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_MASKED_NEW_EQUALS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_14,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_14,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_15 */
	{
		8U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		72U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		83U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn15,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn15,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn15,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_15,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_15,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_MASKED_NEW_EQUALS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_15,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_15,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_16 */
	{
		11U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		85U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		96U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn16,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn16,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn16,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_16,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_16,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_17 */
	{
		20U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		98U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		119U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn17,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn17,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn17,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_17,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_17,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[1],	/* ComIPdu_1 */
		COM_MASKED_NEW_EQUALS_X,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_17,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_17,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_18 */
	{
		13U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		1U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn18,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn18,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn18,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_18,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_18,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_NEW_IS_WITHIN,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_18,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_18,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_19 */
	{
		11U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		17U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		29U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn19,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn19,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn19,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_19,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_19,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_NEW_IS_WITHIN,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_19,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_19,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_20 */
	{
		17U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		34U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		51U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn20,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn20,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn20,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_20,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_20,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_NEW_IS_WITHIN,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_20,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_20,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_21 */
	{
		11U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		53U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		65U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn21,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn21,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn21,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_21,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_21,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_NEW_IS_WITHIN,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_21,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_21,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_22 */
	{
		4U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		68U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		67U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn22,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn22,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn22,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_22,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_22,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_NEW_IS_WITHIN,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_22,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_22,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_23 */
	{
		8U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		72U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		87U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn23,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn23,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn23,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_23,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_23,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_NEW_IS_WITHIN,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_23,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_23,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_24 */
	{
		9U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		92U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		85U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn24,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn24,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn24,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_24,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_24,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_25 */
	{
		18U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		104U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		90U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn25,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn25,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn25,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_25,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_25,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_26 */
	{
		1U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		114U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		116U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn26,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn26,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn26,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_26,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_26,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[2],	/* ComIPdu_2 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_27 */
	{
		13U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		1U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn27,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn27,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn27,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_27,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_27,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_NEW_IS_OUTSIDE,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_27,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_27,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_28 */
	{
		11U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		17U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		29U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn28,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn28,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn28,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_28,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_28,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_NEW_IS_OUTSIDE,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_28,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_28,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_29 */
	{
		17U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		34U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		51U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn29,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn29,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn29,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_29,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_29,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_NEW_IS_OUTSIDE,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_29,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_29,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_30 */
	{
		11U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		53U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		65U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn30,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn30,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn30,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_30,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_30,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_NEW_IS_OUTSIDE,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_30,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_30,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_31 */
	{
		4U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		68U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		67U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn31,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn31,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn31,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_31,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_31,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_NEW_IS_OUTSIDE,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_31,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_31,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_32 */
	{
		8U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		72U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		87U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn32,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn32,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn32,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_32,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_32,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_NEW_IS_OUTSIDE,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_32,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_32,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_33 */
	{
		9U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		92U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		85U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn33,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn33,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn33,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_33,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_33,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_34 */
	{
		18U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		104U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		90U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn34,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn34,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn34,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_34,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_34,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_35 */
	{
		1U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED_ON_CHANGE,	/* ComTransferProperty */
		114U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		116U,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn35,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn35,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn35,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_35,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_35,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[3],	/* ComIPdu_3 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		(void *)&signal_buffer_ComConfig_0_ComSignal_35	/* シグナルバッファ */
	},
	/* ComSignal_36 */
	{
		15U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn36,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn36,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn36,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_36,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_36,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_36,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_36,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_37 */
	{
		3U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		21U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn37,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn37,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn37,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_37,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_37,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_37,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_37,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_38 */
	{
		12U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		42U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn38,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn38,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn38,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_38,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_38,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_38,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_38,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_39 */
	{
		15U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		48U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn39,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn39,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn39,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_39,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_39,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_39,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_39,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_40 */
	{
		1U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		64U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn40,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn40,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn40,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_40,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_40,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_40,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_40,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_41 */
	{
		11U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		68U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn41,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn41,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn41,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_41,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_41,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_41,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_41,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_42 */
	{
		11U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		82U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn42,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn42,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn42,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_42,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_42,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_42,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_42,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_43 */
	{
		10U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		110U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn43,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn43,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn43,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_43,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_43,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_43,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_43,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_44 */
	{
		6U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		116U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn44,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn44,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn44,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_44,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_44,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[4],	/* ComIPdu_4 */
		COM_MASKED_NEW_DIFFERS_MASKED_OLD,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_44,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_44,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_45 */
	{
		4U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		4U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		2U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn45,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn45,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn45,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_45,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_45,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_45,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_45,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_46 */
	{
		13U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		18U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		15U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn46,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn46,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn46,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_46,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_46,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_46,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_46,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_47 */
	{
		20U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		25U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		45U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn47,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn47,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn47,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_47,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_47,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_47,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_47,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_48 */
	{
		7U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		48U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		55U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn48,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn48,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn48,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_48,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_48,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_48,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_48,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_49 */
	{
		6U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		57U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		63U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn49,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn49,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn49,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_49,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_49,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_49,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_49,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_50 */
	{
		5U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		64U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		69U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn50,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn50,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn50,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_50,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_50,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_50,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_50,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_51 */
	{
		13U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		73U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		86U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn51,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn51,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn51,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_51,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_51,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_51,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_51,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_52 */
	{
		7U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		88U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		95U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn52,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn52,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn52,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_52,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_52,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_52,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_52,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_53 */
	{
		COM_INVALID_UINT8,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_OPAQUE,	/* ComSignalEndianness */
		COM_UINT8_N,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		96U,	/* ComBitPosition */
		3U,	/* ComSignalLength */
		120U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn53,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		NULL_PTR,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn53,	/* ComTimeoutNotification */
		(const void *)signal_invalid_value_ComConfig_0_ComSignal_53,	/* ComSignalDataInvalidValue */
		(const void *)signal_init_value_ComConfig_0_ComSignal_53,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_53,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_54 */
	{
		1U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		122U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		121U,	/* ComUpdateBitPosition */
		0U,	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn54,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn54,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn54,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_54,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_54,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[5],	/* ComIPdu_5 */
		COM_ONE_EVERY_N,	/* ComFilterAlgorithm */
		(const void *)&filter_inib_ComConfig_0_ComSignal_54,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_54,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_55 */
	{
		5U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn55,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn55,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn55,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_55,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_55,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_55,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_56 */
	{
		6U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		10U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn56,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn56,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn56,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_56,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_56,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_56,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_57 */
	{
		6U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		26U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn57,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn57,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn57,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_57,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_57,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_57,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_58 */
	{
		14U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		42U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn58,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn58,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn58,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_58,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_58,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_58,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_59 */
	{
		12U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		48U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn59,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn59,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn59,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_59,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_59,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_59,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_60 */
	{
		10U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		62U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn60,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn60,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn60,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_60,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_60,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_60,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_61 */
	{
		14U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		90U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn61,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn61,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn61,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_61,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_61,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_61,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_62 */
	{
		17U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		112U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn62,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn62,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn62,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_62,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_62,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_62,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_63 */
	{
		1U,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		97U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn63,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn63,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn63,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_63,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_63,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_63,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_64 */
	{
		COM_INVALID_UINT8,	/* ComBitSize */
		COM_NOTIFY,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_OPAQUE,	/* ComSignalEndianness */
		COM_UINT8_N,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		120U,	/* ComBitPosition */
		8U,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn64,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn64,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn64,	/* ComTimeoutNotification */
		(const void *)signal_invalid_value_ComConfig_0_ComSignal_64,	/* ComSignalDataInvalidValue */
		(const void *)signal_init_value_ComConfig_0_ComSignal_64,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[6],	/* ComIPdu_6 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_64,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_74 */
	{
		COM_INVALID_UINT8,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_OPAQUE,	/* ComSignalEndianness */
		COM_UINT8_N,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		120U,	/* ComBitPosition */
		8U,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn74,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn74,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn74,	/* ComTimeoutNotification */
		(const void *)signal_invalid_value_ComConfig_0_ComSignal_74,	/* ComSignalDataInvalidValue */
		(const void *)signal_init_value_ComConfig_0_ComSignal_74,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_74,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_66 */
	{
		6U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		10U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn66,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn66,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn66,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_66,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_66,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_66,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_67 */
	{
		6U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		26U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn67,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn67,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn67,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_67,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_67,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_67,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_68 */
	{
		14U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		42U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn68,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn68,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn68,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_68,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_68,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_68,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_69 */
	{
		12U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		48U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn69,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn69,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn69,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_69,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_69,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_69,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_70 */
	{
		10U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		62U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn70,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn70,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn70,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_70,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_70,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_70,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_71 */
	{
		14U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT16,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		90U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn71,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn71,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn71,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_71,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_71,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_71,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_72 */
	{
		17U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		112U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn72,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn72,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn72,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_72,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_72,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_72,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_73 */
	{
		1U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		97U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn73,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn73,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn73,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_73,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_73,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_73,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_65 */
	{
		5U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_SINT8,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(50U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn65,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn65,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn65,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_65,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_65,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[7],	/* ComIPdu_7 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_65,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_75 */
	{
		COM_INVALID_UINT8,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_OPAQUE,	/* ComSignalEndianness */
		COM_UINT8_N,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		0U,	/* ComBitPosition */
		1U,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn75,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn75,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn75,	/* ComTimeoutNotification */
		NULL_PTR,	/* ComSignalDataInvalidValue */
		(const void *)signal_init_value_ComConfig_0_ComSignal_75,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[8],	/* ComIPdu_8 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_76 */
	{
		2U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_PENDING,	/* ComTransferProperty */
		8U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn76,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn76,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn76,	/* ComTimeoutNotification */
		NULL_PTR,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_76,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[8],	/* ComIPdu_8 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_77 */
	{
		1U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		13U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn77,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn77,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn77,	/* ComTimeoutNotification */
		NULL_PTR,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_77,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[8],	/* ComIPdu_8 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_77,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_78 */
	{
		1U,	/* ComBitSize */
		COM_INVALID_UINT8,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		14U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn78,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn78,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn78,	/* ComTimeoutNotification */
		NULL_PTR,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_78,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[8],	/* ComIPdu_8 */
		COM_ALWAYS,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_78,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_79 */
	{
		32U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_FLOAT32,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		40U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn79,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn79,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn79,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_79,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_79,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[8],	/* ComIPdu_8 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_80 */
	{
		64U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_FLOAT64,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		128U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn80,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn80,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn80,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_80,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_80,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[8],	/* ComIPdu_8 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_81 */
	{
		1U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_LITTLE_ENDIAN,	/* ComSignalEndianness */
		COM_BOOLEAN,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		1U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		0U,	/* ComTimeout */
		NULL_PTR,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		NULL_PTR,	/* ComNotification */
		NULL_PTR,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_81,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_81,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[9],	/* ComIPdu_9 */
		COM_INVALID_UINT8,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		NULL_PTR,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_82 */
	{
		COM_INVALID_UINT8,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_OPAQUE,	/* ComSignalEndianness */
		COM_UINT8_N,	/* ComSignalType */
		COM_TRIGGERED,	/* ComTransferProperty */
		0U,	/* ComBitPosition */
		1U,	/* ComSignalLength */
		COM_INVALID_UINT16,	/* ComUpdateBitPosition */
		(75U + 1U),	/* ComFirstTimeout */
		100U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn82,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn82,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn82,	/* ComTimeoutNotification */
		NULL_PTR,	/* ComSignalDataInvalidValue */
		(const void *)signal_init_value_ComConfig_0_ComSignal_82,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[10],	/* ComIPdu_10 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_82,	/* シグナル管理ブロック */
		NULL_PTR	/* シグナルバッファ */
	},
	/* ComSignal_83 */
	{
		5U,	/* ComBitSize */
		COM_REPLACE,	/* ComDataInvalidAction */
		COM_NONE,	/* ComRxDataTimeoutAction */
		COM_BIG_ENDIAN,	/* ComSignalEndianness */
		COM_UINT8,	/* ComSignalType */
		COM_TRIGGERED_ON_CHANGE,	/* ComTransferProperty */
		3U,	/* ComBitPosition */
		COM_INVALID_UINT16,	/* ComSignalLength */
		20U,	/* ComUpdateBitPosition */
		(100U + 1U),	/* ComFirstTimeout */
		125U,	/* ComTimeout */
		&Rte_COMCbkTErr_sn83,	/* ComErrorNotification */
		NULL_PTR,	/* ComInvalidNotification */
		&Rte_COMCbkTAck_sn83,	/* ComNotification */
		&Rte_COMCbkTxTOut_sn35,	/* ComTimeoutNotification */
		(const void *)&signal_invalid_value_ComConfig_0_ComSignal_83,	/* ComSignalDataInvalidValue */
		(const void *)&signal_init_value_ComConfig_0_ComSignal_83,	/* ComSignalInitValue */
		&tx_ipdu_inib_list_ComConfig_0[11],	/* ComIPdu_11 */
		COM_NEVER,	/* ComFilterAlgorithm */
		NULL_PTR,	/* p_filter_inib */
		(void *)&tx_signal_cb_ComConfig_0_ComSignal_83,	/* シグナル管理ブロック */
		(void *)&signal_buffer_ComConfig_0_ComSignal_83	/* シグナルバッファ */
	}
};

/* IPDU管理ブロックリスト：<送受信>_ipdu_cb_list_<ComConfig> */
static TX_IPDU_CB tx_ipdu_cb_list_ComConfig_0[12];

/* 所属シグナルIDリスト：signalid_list_<ComConfig>_<ComIPdu> */
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_0[9] = {
	/* ComSignal_0 */
	0U,
	/* ComSignal_1 */
	1U,
	/* ComSignal_2 */
	2U,
	/* ComSignal_3 */
	3U,
	/* ComSignal_4 */
	4U,
	/* ComSignal_5 */
	5U,
	/* ComSignal_6 */
	6U,
	/* ComSignal_7 */
	7U,
	/* ComSignal_8 */
	8U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_1[9] = {
	/* ComSignal_9 */
	9U,
	/* ComSignal_10 */
	10U,
	/* ComSignal_11 */
	11U,
	/* ComSignal_12 */
	12U,
	/* ComSignal_13 */
	13U,
	/* ComSignal_14 */
	14U,
	/* ComSignal_15 */
	15U,
	/* ComSignal_16 */
	16U,
	/* ComSignal_17 */
	17U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_2[9] = {
	/* ComSignal_18 */
	18U,
	/* ComSignal_19 */
	19U,
	/* ComSignal_20 */
	20U,
	/* ComSignal_21 */
	21U,
	/* ComSignal_22 */
	22U,
	/* ComSignal_23 */
	23U,
	/* ComSignal_24 */
	24U,
	/* ComSignal_25 */
	25U,
	/* ComSignal_26 */
	26U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_3[9] = {
	/* ComSignal_27 */
	27U,
	/* ComSignal_28 */
	28U,
	/* ComSignal_29 */
	29U,
	/* ComSignal_30 */
	30U,
	/* ComSignal_31 */
	31U,
	/* ComSignal_32 */
	32U,
	/* ComSignal_33 */
	33U,
	/* ComSignal_34 */
	34U,
	/* ComSignal_35 */
	35U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_4[9] = {
	/* ComSignal_36 */
	36U,
	/* ComSignal_37 */
	37U,
	/* ComSignal_38 */
	38U,
	/* ComSignal_39 */
	39U,
	/* ComSignal_40 */
	40U,
	/* ComSignal_41 */
	41U,
	/* ComSignal_42 */
	42U,
	/* ComSignal_43 */
	43U,
	/* ComSignal_44 */
	44U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_5[10] = {
	/* ComSignal_45 */
	45U,
	/* ComSignal_46 */
	46U,
	/* ComSignal_47 */
	47U,
	/* ComSignal_48 */
	48U,
	/* ComSignal_49 */
	49U,
	/* ComSignal_50 */
	50U,
	/* ComSignal_51 */
	51U,
	/* ComSignal_52 */
	52U,
	/* ComSignal_53 */
	53U,
	/* ComSignal_54 */
	54U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_6[10] = {
	/* ComSignal_55 */
	55U,
	/* ComSignal_56 */
	56U,
	/* ComSignal_57 */
	57U,
	/* ComSignal_58 */
	58U,
	/* ComSignal_59 */
	59U,
	/* ComSignal_60 */
	60U,
	/* ComSignal_61 */
	61U,
	/* ComSignal_62 */
	62U,
	/* ComSignal_63 */
	63U,
	/* ComSignal_64 */
	64U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_7[10] = {
	/* ComSignal_65 */
	74U,
	/* ComSignal_66 */
	66U,
	/* ComSignal_67 */
	67U,
	/* ComSignal_68 */
	68U,
	/* ComSignal_69 */
	69U,
	/* ComSignal_70 */
	70U,
	/* ComSignal_71 */
	71U,
	/* ComSignal_72 */
	72U,
	/* ComSignal_73 */
	73U,
	/* ComSignal_74 */
	65U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_8[6] = {
	/* ComSignal_75 */
	75U,
	/* ComSignal_76 */
	76U,
	/* ComSignal_77 */
	77U,
	/* ComSignal_78 */
	78U,
	/* ComSignal_79 */
	79U,
	/* ComSignal_80 */
	80U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_9[1] = {
	/* ComSignal_81 */
	81U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_10[1] = {
	/* ComSignal_82 */
	82U
};
static const Com_SignalIdType signalid_list_ComConfig_0_ComIPdu_11[1] = {
	/* ComSignal_83 */
	83U
};

/* IPDU状態：state_<ComConfig>_<ComIPdu> */
static uint8 state_ComConfig_0_ComIPdu_0;
static uint8 state_ComConfig_0_ComIPdu_1;
static uint8 state_ComConfig_0_ComIPdu_2;
static uint8 state_ComConfig_0_ComIPdu_3;
static uint8 state_ComConfig_0_ComIPdu_4;
static uint8 state_ComConfig_0_ComIPdu_5;
static uint8 state_ComConfig_0_ComIPdu_6;
static uint8 state_ComConfig_0_ComIPdu_7;
static uint8 state_ComConfig_0_ComIPdu_8;
static uint8 state_ComConfig_0_ComIPdu_9;
static uint8 state_ComConfig_0_ComIPdu_10;
static uint8 state_ComConfig_0_ComIPdu_11;

/* IPDU所属グループベクタ：ipdu_group_vector_<ComConfig> */
static const Com_IpduGroupVector ipdu_group_vector_ComConfig_0[12] = {
	/* ComIPdu_0 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_1 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_2 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_3 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_4 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_5 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_6 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_7 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_8 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_9 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_10 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))},
	/* ComIPdu_11 (ComIPduGroupHandleId: 0) */
	{(uint8) (1U << (0U - (8U * 0U)))}
};

/* 送信モード(TRUE)初期化ブロック：ipdu_tx_mode_true_inib_<ComConfig>_<ComIPdu> */
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_0 = {
	COM_NONE,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_1 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_2 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_3 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_4 = {
	COM_DIRECT,	/* ComTxModeMode */
	2U,	/* ComTxModeNumberOfRepetitions */
	15U,	/* ComTxModeRepetitionPeriod (3.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_5 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_6 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	15U,	/* ComTxModeRepetitionPeriod (3.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_7 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_8 = {
	COM_MIXED,	/* ComTxModeMode */
	3U,	/* ComTxModeNumberOfRepetitions */
	15U,	/* ComTxModeRepetitionPeriod (3.0 / 0.2) */
	(10U + 1U),	/* ComTxModeTimeOffset ((2.0 / 0.2) + 1) */
	20U	/* ComTxModeTimePeriod (4.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_9 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_10 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_11 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};

/* 送信モード(FALSE)初期化ブロック：ipdu_tx_mode_false_inib_<ComConfig>_<ComIPdu> */
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_0 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_1 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_2 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_3 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_4 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_5 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_6 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_7 = {
	COM_DIRECT,	/* ComTxModeMode */
	2U,	/* ComTxModeNumberOfRepetitions */
	15U,	/* ComTxModeRepetitionPeriod (3.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_8 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_9 = {
	COM_PERIODIC,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(15U + 1U),	/* ComTxModeTimeOffset ((3.0 / 0.2) + 1) */
	25U	/* ComTxModeTimePeriod (5.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_10 = {
	COM_MIXED,	/* ComTxModeMode */
	3U,	/* ComTxModeNumberOfRepetitions */
	15U,	/* ComTxModeRepetitionPeriod (3.0 / 0.2) */
	(10U + 1U),	/* ComTxModeTimeOffset ((2.0 / 0.2) + 1) */
	20U	/* ComTxModeTimePeriod (4.0 / 0.2) */
};
static const TX_MODE_INIB ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_11 = {
	COM_DIRECT,	/* ComTxModeMode */
	0U,	/* ComTxModeNumberOfRepetitions */
	0U,	/* ComTxModeRepetitionPeriod (0.0 / 0.2) */
	(0U + 1U),	/* ComTxModeTimeOffset ((0.0 / 0.2) + 1) */
	0U	/* ComTxModeTimePeriod (0.0 / 0.2) */
};

/* 送信IPDU初期化ブロックリスト : tx_ipdu_inib_<ComConfig>_<ComIPdu> */
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_0 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	15U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_0,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_0	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_1 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	10U,	/* ComTxIPduUnusedAreasDefault */
	0U,	/* ComMinimumDelayTime (0.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_1,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_1	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_2 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	5U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_2,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_2	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_3 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	3U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_3,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_3	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_4 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	6U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_4,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_4	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_5 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	1U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_5,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_5	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_6 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	3U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_6,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_6	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_7 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	12U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_7,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_7	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_8 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	5U,	/* ComTxIPduUnusedAreasDefault */
	5U,	/* ComMinimumDelayTime (1.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_8,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_8	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_9 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	3U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_9,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_9	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_10 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	3U,	/* ComTxIPduUnusedAreasDefault */
	5U,	/* ComMinimumDelayTime (1.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_10,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_10	/* p_tx_mode_false_inib */
};
static const TX_IPDU_INIB tx_ipdu_inib_ComConfig_0_ComIPdu_11 = {
	COM_TRANSMIT,	/* ComTxIPduClearUpdateBit */
	0U,	/* ComTxIPduUnusedAreasDefault */
	10U,	/* ComMinimumDelayTime (2.0 / 0.2) */
	&ipdu_tx_mode_true_inib_ComConfig_0_ComIPdu_11,	/* p_tx_mode_true_inib */
	&ipdu_tx_mode_false_inib_ComConfig_0_ComIPdu_11	/* p_tx_mode_false_inib */
};

/* IPDU初期化ブロックリスト：<送受信>_ipdu_inib_list_<ComConfig> */
static const IPDU_INIB tx_ipdu_inib_list_ComConfig_0[12] = {
	/* ComIPdu_0 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		FALSE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_0,	/* p_tx_ipdu_inib */
		&IPDU_Callout_0,	/* ComIPduCallout */
		0U,	/* PduRSourcePduHandleId */
		15U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_0,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[0],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[0],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_0,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_0,	/* IPDU状態 */
		9U	/* tnum_signal */
	},
	/* ComIPdu_1 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_DEFERRED,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		FALSE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_1,	/* p_tx_ipdu_inib */
		&IPDU_Callout_1,	/* ComIPduCallout */
		1U,	/* PduRSourcePduHandleId */
		15U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_1,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[1],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[1],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_1,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_1,	/* IPDU状態 */
		9U	/* tnum_signal */
	},
	/* ComIPdu_2 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_DEFERRED,	/* ComIPduSignalProcessing */
		COM_TP,	/* ComIPduType */
		FALSE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_2,	/* p_tx_ipdu_inib */
		&IPDU_Callout_2,	/* ComIPduCallout */
		2U,	/* PduRSourcePduHandleId */
		16U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_2,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[2],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[2],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_2,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_2,	/* IPDU状態 */
		9U	/* tnum_signal */
	},
	/* ComIPdu_3 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_TP,	/* ComIPduType */
		TRUE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_3,	/* p_tx_ipdu_inib */
		&IPDU_Callout_3,	/* ComIPduCallout */
		3U,	/* PduRSourcePduHandleId */
		16U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_3,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[3],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[3],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_3,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_3,	/* IPDU状態 */
		9U	/* tnum_signal */
	},
	/* ComIPdu_4 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		FALSE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_4,	/* p_tx_ipdu_inib */
		&IPDU_Callout_4,	/* ComIPduCallout */
		4U,	/* PduRSourcePduHandleId */
		16U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_4,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[4],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[4],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_4,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_4,	/* IPDU状態 */
		9U	/* tnum_signal */
	},
	/* ComIPdu_5 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		FALSE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_5,	/* p_tx_ipdu_inib */
		&IPDU_Callout_5,	/* ComIPduCallout */
		5U,	/* PduRSourcePduHandleId */
		16U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_5,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[5],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[5],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_5,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_5,	/* IPDU状態 */
		10U	/* tnum_signal */
	},
	/* ComIPdu_6 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		FALSE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_6,	/* p_tx_ipdu_inib */
		&IPDU_Callout_6,	/* ComIPduCallout */
		6U,	/* PduRSourcePduHandleId */
		25U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_6,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[6],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[6],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_6,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_6,	/* IPDU状態 */
		10U	/* tnum_signal */
	},
	/* ComIPdu_7 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		TRUE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_7,	/* p_tx_ipdu_inib */
		&IPDU_Callout_7,	/* ComIPduCallout */
		7U,	/* PduRSourcePduHandleId */
		25U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_7,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[7],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[7],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_7,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_7,	/* IPDU状態 */
		10U	/* tnum_signal */
	},
	/* ComIPdu_8 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		TRUE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_8,	/* p_tx_ipdu_inib */
		&IPDU_Callout_8,	/* ComIPduCallout */
		8U,	/* PduRSourcePduHandleId */
		18U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_8,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[8],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[8],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_8,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_8,	/* IPDU状態 */
		6U	/* tnum_signal */
	},
	/* ComIPdu_9 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_TP,	/* ComIPduType */
		TRUE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_9,	/* p_tx_ipdu_inib */
		&IPDU_Callout_9,	/* ComIPduCallout */
		9U,	/* PduRSourcePduHandleId */
		16U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_9,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[9],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[9],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_9,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_9,	/* IPDU状態 */
		1U	/* tnum_signal */
	},
	/* ComIPdu_10 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		TRUE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_10,	/* p_tx_ipdu_inib */
		&IPDU_Callout_10,	/* ComIPduCallout */
		10U,	/* PduRSourcePduHandleId */
		16U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_10,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[10],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[10],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_10,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_10,	/* IPDU状態 */
		1U	/* tnum_signal */
	},
	/* ComIPdu_11 */
	{
		COM_SEND,	/* ComIPduDirection */
		COM_IMMEDIATE,	/* ComIPduSignalProcessing */
		COM_NORMAL,	/* ComIPduType */
		FALSE,	/* ComIPduCancellationSupport */
		&tx_ipdu_inib_ComConfig_0_ComIPdu_11,	/* p_tx_ipdu_inib */
		NULL_PTR,	/* ComIPduCallout */
		11U,	/* PduRSourcePduHandleId */
		10U,	/* PduLength */
		signalid_list_ComConfig_0_ComIPdu_11,	/* 所属シグナルIDリスト */
		&ipdu_group_vector_ComConfig_0[11],	/* IPDU所属グループベクタ */
		(void *)&tx_ipdu_cb_list_ComConfig_0[11],	/* IPDU管理リスト */
		ipdu_buffer_ComConfig_0_ComIPdu_11,	/* IPDUバッファ */
		&state_ComConfig_0_ComIPdu_11,	/* IPDU状態 */
		1U	/* tnum_signal */
	}
};


/* 全IPDU初期化ブロックテーブル(IDソート)：ipdu_inib_table_<ComConfig> */
static const IPDU_INIB *ipdu_inib_table_ComConfig_0[12] = {
	/* ComIPdu_0 */
	&tx_ipdu_inib_list_ComConfig_0[0],
	/* ComIPdu_1 */
	&tx_ipdu_inib_list_ComConfig_0[1],
	/* ComIPdu_2 */
	&tx_ipdu_inib_list_ComConfig_0[2],
	/* ComIPdu_3 */
	&tx_ipdu_inib_list_ComConfig_0[3],
	/* ComIPdu_4 */
	&tx_ipdu_inib_list_ComConfig_0[4],
	/* ComIPdu_5 */
	&tx_ipdu_inib_list_ComConfig_0[5],
	/* ComIPdu_6 */
	&tx_ipdu_inib_list_ComConfig_0[6],
	/* ComIPdu_7 */
	&tx_ipdu_inib_list_ComConfig_0[7],
	/* ComIPdu_8 */
	&tx_ipdu_inib_list_ComConfig_0[8],
	/* ComIPdu_9 */
	&tx_ipdu_inib_list_ComConfig_0[9],
	/* ComIPdu_10 */
	&tx_ipdu_inib_list_ComConfig_0[10],
	/* ComIPdu_11 */
	&tx_ipdu_inib_list_ComConfig_0[11]
};

/* コンフィギュレーション情報テーブル */
const Com_ConfigType com_config[1] = {
	/* ComConfig_0 */
	{
		0U,	/* ComConfigurationId */
		84U,	/* tnum_signal */
		1U,	/* tnum_ipdu_g */
		signal_inib_table_ComConfig_0,	/* p_signal_inib_table */
		1U,	/* tnum_vector */
		12U,	/* tnum_ipdu */
		ipdu_inib_table_ComConfig_0,	/* pp_ipdu_inib_table */
		0U,	/* tnum_rx_ipdu */
		12U,	/* tnum_tx_ipdu */
		NULL_PTR,	/* p_rx_ipdu_inib_list */
		tx_ipdu_inib_list_ComConfig_0,	/* p_tx_ipdu_inib_list */
		COM_INVALID_UINT32,	/* ComRxTimeBase */
		0.2	/* ComTxTimeBase */
	}
};

