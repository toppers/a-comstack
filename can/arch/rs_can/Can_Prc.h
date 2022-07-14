/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2014-2015 by FUJI SOFT INCORPORATED, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
 *  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
 *  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
 *  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 *  $Id: Can_Prc.h 1064 2015-02-12 04:25:57Z shigihara $
 */

#ifndef TOPPERS_CAN_PRC_H
#define TOPPERS_CAN_PRC_H

#include "Can.h"
#include "Can_InlineSymbols.h"
#include "prc_sil.h"


/*
 *  ������
 */

/* �����Хåե��ֹ� */
#define CAN_TX_BUFF_NO(ch)	((ch) * 16U + 15U)

/* �������塼�ʿ�(�������ϰ�:2��15) */
#define CAN_TXQ_NUM			15U

/* ������FIFO�Хåե�(������)�ֹ� */
#define CAN_TXRX_FIFO_BUFF_NO(ch, hrh_no)	((ch) * 3U + (hrh_no))

/* �ӥå������ */
#define CAN_BIT0	0x00000001U
#define CAN_BIT1	0x00000002U
#define CAN_BIT2	0x00000004U
#define CAN_BIT3	0x00000008U
#define CAN_BIT4	0x00000010U
#define CAN_BIT5	0x00000020U
#define CAN_BIT6	0x00000040U
#define CAN_BIT7	0x00000080U
#define CAN_BIT8	0x00000100U
#define CAN_BIT9	0x00000200U
#define CAN_BIT10	0x00000400U
#define CAN_BIT11	0x00000800U
#define CAN_BIT12	0x00001000U
#define CAN_BIT13	0x00002000U
#define CAN_BIT14	0x00004000U
#define CAN_BIT15	0x00008000U
#define CAN_BIT16	0x00010000U
#define CAN_BIT17	0x00020000U
#define CAN_BIT18	0x00040000U
#define CAN_BIT19	0x00080000U
#define CAN_BIT20	0x00100000U
#define CAN_BIT21	0x00200000U
#define CAN_BIT22	0x00400000U
#define CAN_BIT23	0x00800000U
#define CAN_BIT24	0x01000000U
#define CAN_BIT25	0x02000000U
#define CAN_BIT26	0x04000000U
#define CAN_BIT27	0x08000000U
#define CAN_BIT28	0x10000000U
#define CAN_BIT29	0x20000000U
#define CAN_BIT30	0x40000000U
#define CAN_BIT31	0x80000000U

/*
 *  �쥸�������
 */
/* RSCAN0 �Υ١������ɥ쥹 */
#define RSCAN0_BASE			0xFFD00000U

/* �����Х� */
#define RSCAN0GCFG					(*(volatile uint32 *) (RSCAN0_BASE + 0x0084U))
#define RSCAN0GCTR					(*(volatile uint32 *) (RSCAN0_BASE + 0x0088U))
#define RSCAN0GSTS					(*(volatile uint32 *) (RSCAN0_BASE + 0x008CU))
#define RSCAN0GAFLCFG0				(*(volatile uint32 *) (RSCAN0_BASE + 0x009CU))
#define RSCAN0GAFLCFG1				(*(volatile uint32 *) (RSCAN0_BASE + 0x00A0U))
#define RSCAN0GAFLECTR				(*(volatile uint32 *) (RSCAN0_BASE + 0x0098U))

/* ����ͥ� */
#define RSCAN0CmCFG(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0000U + ((ch) * 0x10U)))
#define RSCAN0CmCTR(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0004U + ((ch) * 0x10U)))
#define RSCAN0CmSTS(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0008U + ((ch) * 0x10U)))
#define RSCAN0THLCC(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0400U + ((ch) * 0x04U)))

/* �����롼�� */
#define RSCAN0GAFLID(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0500U + ((rule) * 0x10U)))
#define RSCAN0GAFLM(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0504U + ((rule) * 0x10U)))
#define RSCAN0GAFLP0(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0508U + ((rule) * 0x10U)))
#define RSCAN0GAFLP1(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x050CU + ((rule) * 0x10U)))

/* ������FIFO�Хåե�(������) */
#define RSCAN0CFCC(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0118U + ((buf_no) * 0x04U)))
#define RSCAN0CFSTS(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0178U + ((buf_no) * 0x04U)))
#define RSCAN0CFPCTR(buf_no)		(*(volatile uint32 *) (RSCAN0_BASE + 0x01D8U + ((buf_no) * 0x04U)))
#define RSCAN0CFID(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0E80U + ((buf_no) * 0x10U)))
#define RSCAN0CFPTR(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0E84U + ((buf_no) * 0x10U)))
#define RSCAN0CFDF0(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x0E88U + ((buf_no) * 0x10U) + (byte)))
#define RSCAN0CFDF1(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x0E8CU + ((buf_no) * 0x10U) + (byte)))

/* �����Хåե� */
#define RSCAN0TMID(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x1000U + ((buf_no) * 0x10U)))
#define RSCAN0TMPTR(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x1004U + ((buf_no) * 0x10U)))
#define RSCAN0TMDF0(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x1008U + ((buf_no) * 0x10U) + (byte)))
#define RSCAN0TMDF1(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x100CU + ((buf_no) * 0x10U) + (byte)))
#define RSCAN0TMSTS(buf_no)			(*(volatile uint8  *) (RSCAN0_BASE + 0x02D0U + ((buf_no) * 0x01U)))

/* �������塼 */
#define RSCAN0TXQCC(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x03A0U + ((ch) * 0x04U)))
#define RSCAN0TXQSTS(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x03C0U + ((ch) * 0x04U)))
#define RSCAN0TXQPCTR(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x03E0U + ((ch) * 0x04U)))

/* �������� */
#define RSCAN0THLSTS(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0420U + ((ch) * 0x04U)))
#define RSCAN0THLACC(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x1800U + ((ch) * 0x04U)))
#define RSCAN0THLPCTR(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0440U + ((ch) * 0x04U)))

/* ������FIFO������λ������� */
extern uint16 * const	p_irc_can_rec_addr[6];

/* ��������ߴ�λ�� */
extern uint16 * const	p_irc_can_trx_addr[6];

/* ����ߵ�������ޥ���(��������楳��ȥ���) */
#define ENABLE_ICRCANREC(ch)	(*p_irc_can_rec_addr[(ch)] &= ~CAN_BIT7)
#define ENABLE_ICRCANTRX(ch)	(*p_irc_can_trx_addr[(ch)] &= ~CAN_BIT7)

/* ����߶ػ�����ޥ���(��������楳��ȥ���) */
#define DISABLE_ICRCANREC(ch)	(*p_irc_can_rec_addr[(ch)] |= CAN_BIT7)
#define DISABLE_ICRCANTRX(ch)	(*p_irc_can_trx_addr[(ch)] |= CAN_BIT7)

/* C_ISO_CANOSC����å�ʬ���쥸���� */
#define CKSC_ICANOSCD_CTL			0xFFF8AA00U

/* �����롼�������(ch0��3)�� */
#define GAFLCFG0_REG_BIT_SHIFT(ch)	(24U - ((ch) * 8U))

/* �����롼�������(ch4��5)�� */
#define GAFLCFG1_REG_BIT_SHIFT(ch)	(24U - (((ch) - 4U) * 8U))

/*
 * [CAN077][CAN284][CAN385][CAN386] �������åȰ�¸������
 */
extern const Can_ConfigType	*p_cur_can_config;
extern const CAN_CTRL_INIB	*p_cur_can_ctrl_inib_table;
extern uint8				can_interrupt_nested_cnt[];

/* �����ؿ��ץ�ȥ�������� */
LOCAL_INLINE void port_init(void);
LOCAL_INLINE boolean can_target_init_unit_phase1(const Can_ConfigType *p_can_config);
LOCAL_INLINE boolean can_target_init_controller_phase1(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_init_controller_phase2(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_init_controller_phase3(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_rbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hrh_idx);
LOCAL_INLINE boolean can_target_tbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hth_idx);
LOCAL_INLINE boolean can_target_init_unit_phase2(const Can_ConfigType *p_can_config);
LOCAL_INLINE boolean can_target_change_baudrate(uint8 ctrl_id, const Can_ControllerBaudrateConfigType *p_baudrate_table);
LOCAL_INLINE boolean can_target_start_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_stop_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_sleep_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_wakeup_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_disable_controller_interrupts(uint8 ctrl_id);
LOCAL_INLINE boolean can_target_enable_controller_interrupts(uint8 ctrl_id);
LOCAL_INLINE boolean can_target_check_wakeup(uint8 ctrl_id);
LOCAL_INLINE Can_ReturnType can_target_transmit(uint8 ctrl_id, Can_HwHandleType mb_idx, const Can_PduType *PduInfo);
LOCAL_INLINE boolean can_target_check_and_get_rbox(uint8 ctrl_id, Can_HwHandleType *p_rbox_idx);
LOCAL_INLINE boolean can_target_get_rdata(uint8 ctrl_id, Can_HwHandleType rbox_id, Can_IdType *p_can_id, uint8 *p_can_dlc, uint8 can_sdu[]);
LOCAL_INLINE boolean can_target_check_and_get_tbox(uint8 ctrl_id, Can_HwHandleType *p_tbox_idx);
LOCAL_INLINE Can_StateTransitionType can_target_get_mode(uint8 ctrl_id);
LOCAL_INLINE void can_target_busy_wait(void);

/* RCCAN�ݡ��Ƚ���� */
LOCAL_INLINE void
port_init(void)
{
	/* CAN�ǻ��Ѥ��륯��å�(C_ISO_CANOSC)�� �ᥤ�󥯥�å�(MainOsc)�����ꤹ�� */
	sil_wrw_mem((void *) PROTCMD1, 0x000000A5U);
	sil_wrw_mem((void *) CKSC_ICANOSCD_CTL, 0x00000001U);
	sil_wrw_mem((void *) CKSC_ICANOSCD_CTL, 0xFFFFFFFEU);
	sil_wrw_mem((void *) CKSC_ICANOSCD_CTL, 0x00000001U);

	/* CAN0RX�ݡ���(P10_0)����� */
	sil_wrh_mem((void *) PFCAE(10U), sil_reh_mem((void *) PFCAE(10U)) & ~0x0001U);
	sil_wrh_mem((void *) PFCE(10U), sil_reh_mem((void *) PFCE(10U)) & ~0x0001U);
	sil_wrh_mem((void *) PFC(10U), sil_reh_mem((void *) PFC(10U)) | 0x0001U);
	sil_wrh_mem((void *) PM(10U), sil_reh_mem((void *) PM(10U)) | 0x0001U);
	sil_wrh_mem((void *) PMC(10U), sil_reh_mem((void *) PMC(10U)) | 0x0001U);

	/* CAN0TX�ݡ���(P10_1)����� */
	sil_wrh_mem((void *) PFCAE(10U), sil_reh_mem((void *) PFCAE(10U)) & ~0x0002U);
	sil_wrh_mem((void *) PFCE(10U), sil_reh_mem((void *) PFCE(10U)) & ~0x0002U);
	sil_wrh_mem((void *) PFC(10U), sil_reh_mem((void *) PFC(10U)) | 0x0002U);
	sil_wrh_mem((void *) P(10U), sil_reh_mem((void *) P(10U)) | 0x0002U);
	sil_wrh_mem((void *) PM(10U), sil_reh_mem((void *) PM(10U)) & ~0x0002U);
	sil_wrh_mem((void *) PMC(10U), sil_reh_mem((void *) PMC(10U)) | 0x0002U);

	/* CAN1RX�ݡ���(P0_2)����� */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0004U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0004U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) | 0x0004U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) | 0x0004U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0004U);

	/* CAN1TX�ݡ���(P0_3)����� */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0008U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0008U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) | 0x0008U);
	sil_wrh_mem((void *) P(0U), sil_reh_mem((void *) P(0U)) | 0x0008U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) & ~0x0008U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0008U);

	/* CAN2RX�ݡ���(P0_5)����� */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0020U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0020U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x0020U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) | 0x0020U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0020U);

	/* CAN2TX�ݡ���(P0_4)����� */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0010U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0010U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x0010U);
	sil_wrh_mem((void *) P(0U), sil_reh_mem((void *) P(0U)) | 0x0010U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) & ~0x0010U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0010U);

	/* CAN3RX(P1_2)�ݡ��Ƚ���� */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x0004U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) | 0x0004U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x0004U);

	/* CAN3TX�ݡ���(P1_3)����� */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x0008U);
	sil_wrh_mem((void *) P(1U), sil_reh_mem((void *) P(1U)) | 0x0008U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) & ~0x0008U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x0008U);

	/* CAN4RX(P1_12)�ݡ��Ƚ���� */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x1000U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) | 0x1000U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x1000U);

	/* CAN4TX(P1_13)�ݡ��Ƚ���� */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x2000U);
	sil_wrh_mem((void *) P(1U), sil_reh_mem((void *) P(1U)) | 0x2000U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) & ~0x2000U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x2000U);

	/* CAN5RX(P0_13)�ݡ��Ƚ���� */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) | 0x2000U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x2000U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x2000U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) | 0x2000U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x2000U);

	/* CAN5TX(P0_14)�ݡ��Ƚ���� */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) | 0x4000U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x4000U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x4000U);
	sil_wrh_mem((void *) P(0U), sil_reh_mem((void *) P(0U)) | 0x4000U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) & ~0x4000U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x4000U);

	/* CAN�ȥ�󥷡��Хݡ��Ƚ����(����CanTrcv��¸�ߤ��ʤ����ᡤ�����ǽ��������) */
	sil_wrh_mem((void *) P(2U), sil_reh_mem((void *) P(2U)) & 0xFFC0U);
	sil_wrh_mem((void *) PM(2U), sil_reh_mem((void *) PM(2U)) & 0xFFC0U);
	sil_wrh_mem((void *) PMC(2U), sil_reh_mem((void *) PMC(2U)) & 0xFFC0U);
}

/* [CAN407] Can_Init��unit_phase1 */
LOCAL_INLINE boolean
can_target_init_unit_phase1(const Can_ConfigType *p_can_config)
{
	boolean	ret;

	/* [CAN239] RCCAN�ݡ��Ƚ���� */
	port_init();

	/* CAN��RAM���ꥢ���ơ������ե饰�����å� */
	if ((RSCAN0GSTS & CAN_BIT3) != 0U) {
		ret = FALSE;
		goto error_exit;
	}

	/* �����Х륹�ȥåץ⡼�ɤ��� */
	RSCAN0GCTR &= ~CAN_BIT2;

	/* �����Х�ꥻ�åȥ⡼�ɤ����� */
	RSCAN0GCTR |= CAN_BIT0;

	/* CAN�ǻ��Ѥ��륯��å���CKSCLK_ICANOSC(clk_xincan)������ */
	RSCAN0GCFG |= CAN_BIT4;

	ret = TRUE;

  error_exit:
	return(ret);
}

/* [CAN407] Can_Init��controller_phase1 */
LOCAL_INLINE boolean
can_target_init_controller_phase1(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* ����ͥ륹�ȥåץ⡼�ɤ��� */
	RSCAN0CmCTR(ctrl_id) &= ~CAN_BIT2;

	/* [CAN259] ����ͥ�ꥻ�åȥ⡼�ɤ����� */
	RSCAN0CmCTR(ctrl_id) |= CAN_BIT0;

	return(TRUE);
}

/* [CAN407] Can_Init��controller_phase2 */
LOCAL_INLINE boolean
can_target_init_controller_phase2(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	uint32 txdqc_bit;

	/* �������塼�ʿ����� */
	txdqc_bit = CAN_TXQ_NUM << 8U;

	/* [CAN236][CAN237][CAN419] �쥸�����ν���� */
	/* �������塼���� */
	/* ������װ�:1��å�����������λ�� */
	/* �������塼�ʿ����� */
	RSCAN0TXQCC(ctrl_id) = (CAN_BIT13 | txdqc_bit);

	/* ��������Хåե����� */
	/* ������װ�:1��������ǡ����γ�Ǽ��λ�� */
	/* ��������Хåե�����ߵ��� */
	RSCAN0THLCC(ctrl_id) = (CAN_BIT9 | CAN_BIT8);

	/* ����ȥ��餬4ch�ʾ夫Ƚ��*/
	if (ctrl_id < 4U) {
		/* �����롼�������(ch0��3) */
		RSCAN0GAFLCFG0 |= p_ctrl_inib->tnum_hrh << GAFLCFG0_REG_BIT_SHIFT(ctrl_id);
	}
	else {
		/* �����롼�������(ch4��5) */
		RSCAN0GAFLCFG1 |= p_ctrl_inib->tnum_hrh << GAFLCFG1_REG_BIT_SHIFT(ctrl_id);
	}

	return(TRUE);
}

/* [CAN407] Can_Init��controller_phase3 */
LOCAL_INLINE boolean
can_target_init_controller_phase3(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	return(TRUE);
}

/* [CAN407] Can_Init�������᡼��ܥå�������� */
LOCAL_INLINE boolean
can_target_rbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hrh_idx)
{
	static uint8	rx_rule_index_cnt = 0U;
	uint8			rx_rule_index;
	uint32			filter_mask_id;

	/* �����롼��ơ��֥�񤭹��ߵ��� */
	RSCAN0GAFLECTR |= CAN_BIT8;

	/* �롼���ֹ����� */
	rx_rule_index = rx_rule_index_cnt % 16U;

	/* �ڡ����ֹ椬�ڤ��ؤ�뤫Ƚ�� */
	if (rx_rule_index == 0U) {
		/* �ڡ����ֹ������ */
		RSCAN0GAFLECTR = (CAN_BIT8 | (uint32) (rx_rule_index_cnt / 16U));
	}

	/* �ե��륿�ޥ�������ǥå������� */
	filter_mask_id = GET_RBOX_FILTER_MASK_IDX(ctrl_id, hrh_idx);

	/* �ե��륿�ޥ�����̵ͭȽ�� */
	if (filter_mask_id != CAN_NO_MASK_IDX) {
		/* �ե��륿�ޥ������� */
		RSCAN0GAFLM(rx_rule_index) = (CAN_BIT31 | ((uint32) (p_ctrl_inib->p_filtermask_table[filter_mask_id])));
	}
	else {
		/* �ե��륿�ޥ������� */
		RSCAN0GAFLM(rx_rule_index) = (CAN_BIT31 | 0x07FFU);
	}

	/* �����롼��ID����(CAN-ID�쥸����) */
	RSCAN0GAFLID(rx_rule_index) = (uint32) GET_RBOX_CAN_ID(ctrl_id, hrh_idx);

	/* �����롼���٥�����(HRH) */
	RSCAN0GAFLP0(rx_rule_index) = hrh_idx << 16U;

	/* �����롼�����Ѥ���������FIFO�Хåե�(������)�λ��� */
	RSCAN0GAFLP1(rx_rule_index) = 1U << (8U + CAN_TXRX_FIFO_BUFF_NO(ctrl_id, hrh_idx));

	/*
	 *  ������FIFO�Хåե�(������)����
	 *  1��å�����������˳���ߤ������
	 */
	RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, hrh_idx)) = (CAN_BIT12 | CAN_BIT9);

	/* �����롼�륤��ǥå����򥤥󥯥���� */
	rx_rule_index_cnt++;

	/* �����롼��ơ��֥�񤭹��߶ػ� */
	RSCAN0GAFLECTR &= ~CAN_BIT8;

	return(TRUE);
}

/* [CAN407] Can_Init�������᡼��ܥå�������� */
LOCAL_INLINE boolean
can_target_tbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hth_idx)
{
	return(TRUE);
}

/* [CAN407] Can_Init��unit_phase2 */
LOCAL_INLINE boolean
can_target_init_unit_phase2(const Can_ConfigType *p_can_config)
{
	/* �����Х�ꥻ�åȥ⡼�ɤ��饰���Х�ư��⡼�ɤ����� */
	RSCAN0GCTR &= ~(CAN_BIT1 | CAN_BIT0);

	return(TRUE);
}

/* Can_ChangeBaudrate */
LOCAL_INLINE boolean
can_target_change_baudrate(uint8 ctrl_id, const Can_ControllerBaudrateConfigType *p_baudrate_table)
{
	/* [CAN255] �ܡ��졼��������Ƚ�� */
	if (p_baudrate_table->CanControllerBaudRate == 250U) {
		/* ����ͥ륳��ե����졼���������(�ܡ��졼��:250kbps) */
		RSCAN0CmCFG(ctrl_id) = RSCAN_BRP_250;
	}
	else {
		/* ����ͥ륳��ե����졼���������(�ܡ��졼��:500kbps) */
		RSCAN0CmCFG(ctrl_id) = RSCAN_BRP_500;
	}

	return(TRUE);
}

/* Can_SetControllerMode��CAN_T_START */
LOCAL_INLINE boolean
can_target_start_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	uint8 i;

	/* [CAN261] ����ͥ��̿��⡼�ɤ����� */
	RSCAN0CmCTR(ctrl_id) &= ~(CAN_BIT1 | CAN_BIT0);

	/* ����ͥ��̿��⡼�ɤˤʤ�ޤǥ롼��(#67) */
	while ((RSCAN0CmSTS(ctrl_id) &CAN_BIT7) == 0U) {
	}

	/* �������塼����̵ͭ���� */
	RSCAN0TXQCC(ctrl_id) |= CAN_BIT0;

	/* ��������Хåե�����̵ͭ���� */
	RSCAN0THLCC(ctrl_id) |= CAN_BIT0;

	/* [CAN204][CAN425] ����߶ػߥͥ��ȥ������Ƚ�� */
	if (can_interrupt_nested_cnt[ctrl_id] == 0U) {
		/*
		 *  [CAN196] ����ߵ��Ľ���
		 *  ������FIFO�Хåե�(������)�γ���ߵ��Ĥ������
		 *  �Ԥ�����������FIFO�Хåե�(������)�λ���̵ͭ
		 *  ��������˼»ܤ���
		 */
		can_target_enable_controller_interrupts(ctrl_id);
	}

	/* ������FIFO�Хåե�(������)����̵ͭ���� */
	for (i = 0; i < p_ctrl_inib->tnum_hrh; i++) {
		RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) |= CAN_BIT0;
	}

	return(TRUE);
}

/* Can_SetControllerMode��CAN_T_STOP */
LOCAL_INLINE boolean
can_target_stop_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* [CAN204][CAN426] ����߶ػߥͥ��ȥ������Ƚ�� */
	if (can_interrupt_nested_cnt[ctrl_id] == 0U) {
		/* [CAN197] ����߶ػ߽��� */
		can_target_disable_controller_interrupts(ctrl_id);
	}

	/* [CAN263] ����ͥ�ꥻ�åȥ⡼�ɤ����� */
	RSCAN0CmCTR(ctrl_id) &= 0xFFFFFFFDU;

	return(TRUE);
}

/* Can_SetControllerMode��CAN_T_SLEEP */
LOCAL_INLINE boolean
can_target_sleep_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* CAN_T_SLEEP��̤���ݡ��� */
	return(FALSE);
}

/* Can_SetControllerMode��CAN_T_WAKEUP */
LOCAL_INLINE boolean
can_target_wakeup_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* CAN_T_WAKEUP��̤���ݡ��� */
	return(FALSE);
}

/* Can_DisableControllerInterrupts */
LOCAL_INLINE boolean
can_target_disable_controller_interrupts(uint8 ctrl_id)
{
	uint8 i;

	/* ������FIFO�Хåե���������߶ػ�(CAN_BIT1�򥯥ꥢ) */
	for (i = 0; i < GET_HRH_NUM(ctrl_id); i++) {
		RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) &= 0xFFFFFFFDU;
	}

	/* ��������Хåե�����߶ػ�(CAN_BIT8�򥯥ꥢ) */
	RSCAN0THLCC(ctrl_id) &= 0xFFFFFEFFU;

	DISABLE_ICRCANREC(ctrl_id);
	DISABLE_ICRCANTRX(ctrl_id);

	return(TRUE);
}

/* Can_EnableControllerInterrupts */
LOCAL_INLINE boolean
can_target_enable_controller_interrupts(uint8 ctrl_id)
{
	uint8 i;

	/* ������FIFO�Хåե���������ߵ��� */
	for (i = 0; i < GET_HRH_NUM(ctrl_id); i++) {
		RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) |= CAN_BIT1;
	}

	/* ��������Хåե�����ߵ��� */
	RSCAN0THLCC(ctrl_id) |= CAN_BIT8;

	ENABLE_ICRCANREC(ctrl_id);
	ENABLE_ICRCANTRX(ctrl_id);

	return(TRUE);
}

/* Can_CheckWakeup */
LOCAL_INLINE boolean
can_target_check_wakeup(uint8 ctrl_id)
{
	/* �����������åפ�̤���ݡ��� */
	return(FALSE);
}

/* Can_Write�������ǡ����ڤ������׵����� */
LOCAL_INLINE Can_ReturnType
can_target_transmit(uint8 ctrl_id, Can_HwHandleType mb_idx, const Can_PduType *PduInfo)
{
	Can_ReturnType	ret;
	uint8			i;
	uint32			tm_bit;

	/* �����׵�Ƚ�� */
	if ((RSCAN0TXQSTS(ctrl_id) &CAN_BIT1) == 0U) {
		/* CAN-ID���� */
		RSCAN0TMID(CAN_TX_BUFF_NO(ctrl_id)) = (CAN_BIT29 + ((uint32) PduInfo->id));

		/* DLC��������٥������� */
		tm_bit = (uint32) PduInfo->length << 28U;
		tm_bit |= (uint32) mb_idx << 16U;

		/* DLC��������٥����� */
		RSCAN0TMPTR(CAN_TX_BUFF_NO(ctrl_id)) = tm_bit;

		/* [CAN059][CAN427] �ǡ�����Ǽ */
		/* �ǡ�������(0��3�Х���) */
		for (i = 0U; i < 4U; i++) {
			RSCAN0TMDF0(CAN_TX_BUFF_NO(ctrl_id), i) = PduInfo->sdu[i];
		}

		/* 4�Х��ȰʹߤΥ�å�����̵ͭȽ�� */
		if (PduInfo->length > 4U) {
			/* �ǡ�������(4��7�Х���) */
			for (i = 4U; i < PduInfo->length; i++) {
				RSCAN0TMDF1(CAN_TX_BUFF_NO(ctrl_id), (i - 4U)) = PduInfo->sdu[i];
			}
		}
	}
	else {
		ret = CAN_BUSY;
		goto error_exit;
	}

	/* �����׵�(RSCAN0TXQPCTR.TXQPC) */
	RSCAN0TXQPCTR(ctrl_id) = 0xFFU;

	ret = CAN_OK;

  error_exit:
	return(ret);
}

/* Can_IsrRx�������᡼��ܥå������� */
LOCAL_INLINE boolean
can_target_check_and_get_rbox(uint8 ctrl_id, Can_HwHandleType *p_rbox_idx)
{
	boolean	ret;
	uint8	i;
	uint32	rx_rabel;

	/* HRH�����(DET���֤Υ��顼������) */
	*p_rbox_idx = 0xFFU;

	for (i = 0; i < GET_HRH_NUM(ctrl_id); i++) {
		/* ̤�ɥ�å�����̵ͭ��ǧ(RSCAN0CFSTS.CFEMP) */
		if ((RSCAN0CFSTS(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) & CAN_BIT0) == 0U) {
			ret = TRUE;

			/* ������٥����(HRH) */
			rx_rabel = RSCAN0CFPTR(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) & 0x0FFF0000U;

			/* HRH���� */
			*p_rbox_idx = (Can_HwHandleType) (rx_rabel >> 16U);

			break;
		}
		else {
			/* �᡼��ܥå����˼����ǡ���̵�� */
			ret = FALSE;
		}
	}

	return(ret);
}

/* Can_IsrRx������ID�Υǡ������� */
LOCAL_INLINE boolean
can_target_get_rdata(uint8 ctrl_id, Can_HwHandleType rbox_id, Can_IdType *p_can_id, uint8 *p_can_dlc, uint8 can_sdu[])
{
	uint8	i;
	uint8	local_dlc;

	/* CAN-ID����(RSCAN0CFID.CFID) */
	*p_can_id = (Can_IdType) RSCAN0CFID(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id));

	/* DLC����(RSCAN0CFPTR.CFDLC) */
	local_dlc = (uint8) (RSCAN0CFPTR(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)) >> 28U);
	*p_can_dlc = local_dlc;

	/* [CAN012][CAN060][CAN299][CAN300] �ǡ������� */
	/* �ǡ�����Ǽ(0��3�Х���) */
	for (i = 0U; i < 4U; i++) {
		can_sdu[i] = RSCAN0CFDF0((CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)), i);
	}

	/* �ǡ�����4byte�ʾ夫Ƚ�� */
	if (local_dlc > 4U) {
		/* �ǡ�����Ǽ(4��7�Х���) */
		for (i = 4U; i < local_dlc; i++) {
			can_sdu[i] = RSCAN0CFDF1((CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)), (i - 4U));
		}
	}

	/* �꡼�ɥݥ��󥿰�ư(RSCAN0CFPCTR.CFPC) */
	RSCAN0CFPCTR(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)) = 0xFFU;

	/* [CAN420] ������FIFO����������׵�ե饰���ꥢ */
	RSCAN0CFSTS(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)) &= ~CAN_BIT3;

	return(TRUE);
}

/* Can_IsrTx�������᡼��ܥå��������å����� */
LOCAL_INLINE boolean
can_target_check_and_get_tbox(uint8 ctrl_id, Can_HwHandleType *p_tbox_idx)
{
	boolean	ret;

	/* ��������Хåե�������Ƚ�� */
	if ((RSCAN0THLSTS(ctrl_id) &CAN_BIT0) == 0U) {
		/* �᡼��ܥå�������ǥå���(������٥�)���� */
		*p_tbox_idx = (Can_HwHandleType) (RSCAN0THLACC(ctrl_id) >> 8U);

		/* ��������Хåե��Υ꡼�ɥݥ��󥿰�ư */
		RSCAN0THLPCTR(ctrl_id) = 0xFFU;

		ret = TRUE;
	}
	else {
		/* [CAN420] �������������׵�ե饰���ꥢ */
		RSCAN0THLSTS(ctrl_id) &= ~CAN_BIT3;

		/* ̤�꡼�ɤΥ᡼��ܥå���̵�� */
		ret = FALSE;
	}

	return(ret);
}

LOCAL_INLINE Can_StateTransitionType
can_target_get_mode(uint8 ctrl_id)
{
	Can_StateTransitionType	ret;
	uint32					cmsts_reg;

	/* ����ͥ�⡼�ɼ��� */
	cmsts_reg = RSCAN0CmSTS(ctrl_id);

	/* [CAN384][CAN409][CAN410] ư��⡼��Ƚ�� */
	if ((cmsts_reg & CAN_BIT7) != 0U) {
		ret = CAN_T_START;
	}
	else {
		ret = CAN_T_STOP;
	}

	return(ret);
}

/* Can_MainFunction_Write */
LOCAL_INLINE boolean
can_target_polling_tx(uint8 ctrl_id)
{
	/* �ݡ���󥰤ˤ��������̤���ݡ��� */
	return(FALSE);
}

/* Can_MainFunction_Read */
LOCAL_INLINE boolean
can_target_polling_rx(uint8 ctrl_id)
{
	/* �ݡ���󥰤ˤ��������̤���ݡ��� */
	return(FALSE);
}

/* Can_MainFunction_BusOff */
LOCAL_INLINE boolean
can_target_polling_busoff(uint8 ctrl_id)
{
	/* �Х����ս�����̤���ݡ��� */
	return(FALSE);
}

/* Can_MainFunction_Wakeup */
LOCAL_INLINE boolean
can_target_polling_wakeup(uint8 ctrl_id)
{
	/* �����������åפ�̤���ݡ��� */
	return(FALSE);
}

LOCAL_INLINE void
can_target_busy_wait(void)
{
	volatile uint32 i;

	/* �ӥ����������Ƚ��� */
	for (i = 0U; i < 100000U; i++) {
	}
}

/*
 *  ����¸���Ǥ�̤���ݡ��ȵ�ǽ
 *    <CAN048><CAN294><CAN361><CAN461> �����������åפ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN257><CAN265><CAN267><CAN411><CAN412> �ϡ��ɥ�������SLEEP�⡼�ɤ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN282><CAN283> ��������󥻥��̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN258><CAN290><CAN404><CAN405>����Ū��SLEEP�⡼�ɤ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN238><CAN242><CAN391><CAN244> fl850f1l�Ǥ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN062><CAN256><CAN260><CAN422><CAN453> �ܡ��졼�Ȥ�����ϸ���Τ��ᡤ�б����ʤ�
 *    <CAN272><CAN273><CAN274> �Х����ս�����̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 */

#endif /* TOPPERS_CAN_PRC_H */
