$
$  TOPPERS/A-CAN
$      Automotive CAN
$
$  Copyright (C) 2014 by FUJI SOFT INCORPORATED, JAPAN
$
$  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
$  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
$  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
$  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
$      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
$      ����������˴ޤޤ�Ƥ��뤳�ȡ�
$  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
$      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
$      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
$  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
$      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
$      �ȡ�
$    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
$        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
$    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
$        ��𤹤뤳�ȡ�
$  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
$      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
$      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
$      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
$      ���դ��뤳�ȡ�
$
$  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
$  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
$  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
$  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
$
$  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
$  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
$  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
$  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
$  ����Ǥ�����ʤ���
$
$  $Id: Can_Target.tf 599 2014-10-17 01:27:58Z shigihara $
$

$ ====================================================================
$     A-CAN�������åȰ�¸�ƥ�ץ졼�ȡ�NIOS2_DEV�ѡ�
$ ====================================================================

$ ====================================================================
$ ���¸���������
$ ====================================================================
$ // ����ȥ���������
$TARGET_TMAX_CONTROLLER_NUM = 1$

$ // �ե��륿�ޥ��������
$TARGET_TMAX_FILTERMASK_NUM = 32$

$ // ���ݡ��ȥܡ��졼��
$TARGET_SUPPORT_BAUDRATE_LIST = {500, 250}$

$ ====================================================================
$ ��¸���������
$ ====================================================================
$ // �����᡼��ܥå��������
$TMAX_RX_MB_NUM = 32$

$ // �����᡼��ܥå��������
$TMAX_TX_MB_NUM = 16$

$ ====================================================================
$ [CAN022][CAN024] ��¸��Ƚ��ؿ�
$ ====================================================================
$ // �᡼��ܥå����������å�
$FUNCTION CHECK_MAILBOX_NUM$
	$IF ((ARGV[2] <= TMAX_RX_MB_NUM) && (ARGV[3] <= TMAX_TX_MB_NUM))$
		$RESULT = 1$
	$ELSE$
		$RESULT = 0$
	$END$
$END$

$ ====================================================================
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ ====================================================================
$INCLUDE "can.tf"$