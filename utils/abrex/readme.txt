
	ABREX - AUTOSAR BSW and RTE XML Generator -

�ܥɥ�����Ȥϡ�ABREX����Ѥ��뤿���ɬ�פʻ�������������ΤǤ��롥

----------------------------------------------------------------------
ABREX
    AUTOSAR BSW and RTE XML Generator

Copyright (C) 2013-2015 by Center for Embedded Computing Systems
            Graduate School of Information Science, Nagoya Univ., JAPAN
Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
Copyright (C) 2013-2015 by FUJI SOFT INCORPORATED, JAPAN
Copyright (C) 2014-2015 by NEC Communication Systems, Ltd., JAPAN
Copyright (C) 2013-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
Copyright (C) 2013-2015 by Sunny Giken Inc., JAPAN
Copyright (C) 2013-2015 by TOSHIBA CORPORATION, JAPAN
Copyright (C) 2013-2015 by Witz Corporation

�嵭����Ԥϡ��ʲ��� (1)��(3)�ξ������������˸¤ꡤ�ܥɥ����
��ȡ��ܥɥ�����Ȥ���Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
�ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
(1) �ܥɥ�����Ȥ����Ѥ�����ˤϡ��嵭�����ɽ�����������Ѿ��
    ����Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥɥ��������˴ޤޤ��
    ���뤳�ȡ�
(2) �ܥɥ�����Ȥ���Ѥ�����ˤϡ��ɥ�����Ȥ���Ѥ����ݤε���
    �򡤲��Ѹ�Υɥ��������˴ޤ�뤳�ȡ������������Ѹ�Υɥ����
    ��Ȥ���TOPPERS�ץ������Ȼ���γ�ȯ����ʪ�Ǥ�����ˤϡ����θ�
    ��ǤϤʤ���
(3) �ܥɥ�����Ȥ����Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»��
    ����⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ��ޤ���
    �ܥɥ�����ȤΥ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���ͳ�˴��
    �����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�

�ܥɥ�����Ȥϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻���
�˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������ΤǤϤ�
����AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū�����Ѥ���
�Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥

�ܥɥ�����Ȥϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ���
��TOPPERS�ץ������Ȥϡ��ܥɥ�����Ȥ˴ؤ��ơ�����λ�����Ū���Ф�
��Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥɥ�����Ȥ�����
�ˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ����
��ʤ���

$Id: readme.txt 8495 2014-03-10 03:25:35Z shigihara $
----------------------------------------------------------------------

����������������������������������������������������������������������
(1) ABREX����
����������������������������������������������������������������������

ABREX�ϡ�OS��COM��Ϥ�Ȥ���BSW�ȡ�RTE�Υ���ե�����졼�����ե�����
(XML)����������ġ���Ǥ��롥YAML�ե����ޥåȤǵ��Ҥ�������ե�����졼
������������ϤȤ��ơ��б�����XML���������롥

����������������������������������������������������������������������
(2) �Ȥ���
����������������������������������������������������������������������
����������������������������������������������������������������������
(2.1) ư��Ķ�
����������������������������������������������������������������������

ABREX��Ruby�ˤ�äƵ��Ҥ���Ƥ��뤿�ᡤRuby�μ¹ԴĶ���ɬ�פǤ��롥
Cygwin�˴ޤޤ��ʲ��ΥС�������Ruby��ư���ǧ�ѤߤǤ��롥

ruby 1.9.3p327 (2012-11-10 revision 37606) [i386-cygwin]

����������������������������������������������������������������������
(2.2) ����ƥʾ��������
����������������������������������������������������������������������
���ܼ��ϴ���param_info.yaml��¸�ߤ����硤���פǤ���

-p���ץ����ˡ�AUTOSAR�����������Ƥ���ECU����ե�����졼�����ѥ�
�᡼������ƥʾ���ե�����(*)������Ȥ���Ϳ�����¹Ԥ��롥
(*)http://www.autosar.org
   Methodology and Templates -> Templates -> Standard Specifications
    -> AUTOSAR_MOD_ECUConfigurationParameters.zip
   ���ह���"AUTOSAR_MOD_ECUConfigurationParameters.arxml"�Ȥʤ�

$ ruby abrex.rb -p AUTOSAR_MOD_ECUConfigurationParameters.arxml

�ƥѥ�᡼������ƥʤΥǡ��������������ȷ��λ��������ʤɤ���
param_info.yaml�˽��Ϥ���롥

����������������������������������������������������������������������
(2.3) YAML�ե�����κ���
����������������������������������������������������������������������
����������XML�ե�����ξ����YAML�ե����ޥåȤǵ��Ҥ��롥
���Ǿ�̤Υ쥤�䤬�ѥå�����̾�����μ���ECU�⥸�塼��̾�Ȥʤ롥
��ECU�⥸�塼��̾�β��˳����⥸�塼��˴ޤޤ��ѥ�᡼��̾�򥭡��Ȥ��ơ�
  �ѥ�᡼������ƥʤ��ͤ�ϥå�������ǵ��Ҥ��롥
�����֥���ƥʤϡ��ϥå����ͥ��Ȥ��뤳�Ȥ�ɽ�����롥
������ƥʤؤλ��Ȥϡ�YAML�ե��������������ѥå�����̾�˽��äƥѥ���
  ���Ҥ��롥

��OS����

Os:
  Os:
    MainApp:
      DefinitionRef: OsAppMode
    OsOS:
      OsStackMonitoring: 1
      OsStatus: EXTENDED
      OsUseGetServiceId: 1
      OsUseParameterAccess: 1
      OsScalabilityClass: SC1
      OsHooks:
        OsErrorHook: 0
        OsPostTaskHook: 0
        OsPreTaskHook: 0
        OsProtectionHook: 0
        OsShutdownHook: 0
        OsStartupHook: 0
      OsHookStack:
        OsHookStackSize: 1024
      OsOsStack:
        OsOsStackSize: 1024
    TASK1:
      DefinitionRef: OsTask
      OsTaskActivation: 1
      OsTaskPriority: 10
      OsTaskSchedule: FULL
      OsTaskStackSize: 1024
      OsTaskEventRef: /Os/Os/EVENT1
      OsTaskAutostart:
        OsTaskAppModeRef: /Os/Os/MainApp
    EVENT1:
      DefinitionRef: OsEvent

����������������������������������������������������������������������
(2.4) XML�ե����������
����������������������������������������������������������������������
��������YAML�ե����������Ȥ��ơ�abrex.rb��¹Ԥ��롥

$ ruby abrex.rb ./sample.yaml

���Ϥ���YAML�ե�����ξ�����б�����XML�ե����뤬�����ϥե�����̾�γ�ĥ
�Ҥ�arxml���ѹ������ե�����˽��Ϥ���롥
���嵭��ξ�硤sample.arxml

��(2.1)����������param_info.yaml�˴ޤޤ�ʤ�����̾���о줷����硤����
  ����λ���롥
�����֥���ƥ�̾��param_info.yaml�˴ޤޤ줺��YAML�ե�����˵��Ҥ���̾��
  ����������ΤȤ��ơ����֥���ƥʤ��������롥
�������ͤ����������Υ����å��ϰ��ڹԤ�ʤ���

������YAML�ե������ʣ�����ꤹ�뤳�Ȥ��Ǥ������٤Ƥ�YAML�ե�����ξ���
��ޡ�������XML�ե�������������롥Ʊ���ѥ��Υ���ƥʤ��ۤʤ�ե������
¸�ߤ����硤1�ĤΥ���ƥʤ˥ޡ������롥�㤨�С��ʲ���a.yaml��b.yaml��
���Ϥ�����硤MAIN_HW_COUNTER�ˤ�ξ���Υե�����˻��ꤵ�줿���٤ƤΥѥ�
�᡼�������ꤵ�줿XML�ե�����Ȥʤ롥

��a.yaml��
Os:
  Os:
    MAIN_HW_COUNTER:
      DefinitionRef: OsCounter
      OsCounterMaxAllowedValue: 0x7FFFFFFF
      OsCounterTicksPerBase: 10
      OsCounterMinCycle: 4000
      OsCounterType: HARDWARE
      OsSecondsPerTick: 1.666666e-08
      OsCounterIsrRef: /Os/Os/ISR1

��b.yaml��
Os:
  Os:
    MAIN_HW_COUNTER:
      OsCounterAccessingApplication: OSAP1

��Ʊ���ѥ��Υѥ�᡼����ʣ���Υե�����˴ޤޤ����ϡ�¿���٤�*��Ƚ��
  ���ơ�ʣ���Υ���ƥʤ��������롥(�ѥ�᡼�����¿���پ�����ݻ����ʤ�)

����������������������������������������������������������������������
(3) ����¾�ε�ǽ
����������������������������������������������������������������������
����������������������������������������������������������������������
(3.1) XML����YAML���������(���Ѵ�)
����������������������������������������������������������������������
ABREX�Ǥϡ������Ѥߤ�XML�ե����뤫�顤YAML�ե������������뤳�Ȥ�����
�롥-i���ץ����ˡ�AUTOSAR����XML������Ȥ���Ϳ�����¹Ԥ��롥

$ ruby abrex.rb -i sample.arxml

���Ϥ���XML�ե�����ξ�����б�����YAML�ե����뤬�����ϥե�����̾�γ�ĥ
�Ҥ�yaml���ѹ������ե�����˽��Ϥ���롥
���嵭��ξ�硤sample.yaml

����������������������������������������������������������������������
(3.2) �����ͥ졼����csv�ե����������
����������������������������������������������������������������������
TOPPERS/ATK2�ǻ��Ѥ��른���ͥ졼��(cfg.exe)��XML����ƥʾ����CSV�ե���
���Ϳ����ɬ�פ����뤬��ECU����ե�����졼�����ѥ�᡼������ƥʾ���
�ե����뤫���������뤳�Ȥ���ǽ�Ǥ��롥-c���ץ����ˡ�ECU����ե������
�������ѥ�᡼������ƥʾ���ե����������Ȥ���Ϳ����-b���ץ����ˡ�
���������оݤΥ⥸�塼��̾(*)������Ȥ���Ϳ�����¹Ԥ��롥

(*)http://www.autosar.org
   Software Architecture -> General -> AUTOSAR_TR_BSWModuleList.pdf
   �嵭�ե�����˵��ꤵ��Ƥ���Module abbreviation�ǻ��ꤹ�롥

$ ruby abrex.rb -b Com -c AUTOSAR_MOD_ECUConfigurationParameters.arxml

���ꤷ���оݤΥ⥸�塼��̾��CSV�ե�����˽��Ϥ���롥
���嵭��ξ�硤Com.csv

����ջ����
��������CSV�ե�����Υ���ƥʤ�û��̾�ϡ�����ƥ�̾�򤽤Τޤ޻��Ѥ��롥
���äơ�Ʊ��̾�ΤΥ���ƥʤ��ۤʤ륳��ƥʤΥ��֥���ƥʤȤ���¸�ߤ���
���ϡ������ͥ졼���¹Ի��˶��̤Ǥ��ʤ��ʤ롥���ξ�硤��ư�Ƕ��̤Ǥ�
��褦�˽�������ɬ�פ����롥

(��)Com��ComTxModeFalse��ComTxModeTrue�˴ޤޤ��ComTxMode����ƥ�
/AUTOSAR/EcucDefs/Com/ComConfig/ComIPdu/ComTxIPdu/ComTxModeFalse/ComTxMode,ComTxMode,,1
/AUTOSAR/EcucDefs/Com/ComConfig/ComIPdu/ComTxIPdu/ComTxModeTrue/ComTxMode,ComTxMode,,1

����������������������������������������������������������������������
(4) ��ջ���
����������������������������������������������������������������������
����������������������������������������������������������������������
(4.1) ECU����ե�����졼�����ѥ�᡼������ƥʾ���ե�����θ�����
����������������������������������������������������������������������
����ƥʾ��������(�ܥɥ�����Ȥ�2.2�Ϥ򻲾�)�ˤ����ƻ��Ѥ��Ƥ��롤
ECU����ե�����졼�����ѥ�᡼������ƥʾ���ե�����Ǥ���
AUTOSAR_MOD_ECUConfigurationParameters.arxml�θ���������ɬ�פ����롥

����Ƚ�����Ƥ������ʲ��˼�����

��(��)WdgMInternallCheckpointFinalRef
  (��)WdgMInternalCheckpointFinalRef


�ʾ�
