#!ruby -Ke
#
#  TOPPRES/A-COM
#      Automotive COM
#
#  Copyright (C) 2013-2015 by Center for Embedded Computing Systems
#                             Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd.
#  Copyright (C) 2013-2015 by FUJI SOFT INCORPORATED, JAPAN
#  Copyright (C) 2014-2015 by FUJITSU TEN LIMITED.
#  Copyright (C) 2014-2015 by NEC Communication Systems, Ltd., JAPAN
#  Copyright (C) 2013-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
#  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
#  Copyright (C) 2014-2015 by SCSK Corporation
#  Copyright (C) 2013-2015 by Sunny Giken Inc., JAPAN
#  Copyright (C) 2013-2015 by TOSHIBA CORPORATION, JAPAN
#  Copyright (C) 2013-2015 by Witz Corporation
#
#  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
#  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
#  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
#  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
#      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
#      ����������˴ޤޤ�Ƥ��뤳�ȡ�
#  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
#      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
#      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
#  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
#      �ȡ�
#    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
#        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
#    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
#        ��𤹤뤳�ȡ�
#  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
#      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
#      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
#      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
#      ���դ��뤳�ȡ�
#
#  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
#  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
#  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
#  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
#
#  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
#  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
#  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
#  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
#  ����Ǥ�����ʤ���
#
#  $Id: get_spec_id.rb 1241 2015-03-25 07:26:02Z panasonic-ayane $
#

#=====================================================================
# �ƥ����ȥե�����(com_spec.txt)���顤COM�˴ؤ�����ͥ�����ȴ���Ф��ơ�
# ID������ե�����ؽ��Ϥ���
# ���ƥ����ȥե�����ϡ��������ͽ��Word�����Ѵ���ǽ����Ѥ��ƺ�������
#=====================================================================

# �񤭽Ф��ե�����
sWriteFileId = File.dirname(__FILE__) + "/com_spec_id.txt"

# pdf�����ɤ߽Ф����ƥ����ȥǡ���
sTextFile = "com_spec.txt"

# �ƥ����ȥե�������ɤ߹���
sText = File.read(sTextFile)

# ���Ԥ���(����������ǲ��Ԥ����륱�����б�)
sText.gsub!("\r\n", "")
sText.gsub!("\r", "")
sText.gsub!("\n", "")

# �оݥ����򸡺�����
aData1 = sText.scan(/\WCOM[0-9][0-9][0-9]\W/)
aData2 = sText.scan(/COM[0-9][0-9][0-9]_Conf/)
aData3 = sText.scan(/COMa[0-9][0-9][0-9]/)
aData4 = sText.scan(/NCOM[0-9][0-9][0-9]/)

# ������줿���ͥ���
aDelTag = []

# ���פ�ʸ�������
aTmp = []
aData1.each{|sTag|
  if (sTag.include?("��"))
    aDelTag.push(sTag.gsub(/\W(COM[0-9][0-9][0-9])\W/, "\\1"))
  else
    aTmp.push(sTag.gsub(/\W(COM[0-9][0-9][0-9])\W/, "\\1"))
  end
}
aData1 = aTmp

# ��ʣ����ID����
aData1.uniq!
aData2.uniq!
aData3.uniq!
aData4.uniq!

# �����ο����¬
nData1 = aData1.size()
nData2 = aData2.size()
nData3 = aData3.size()
nData4 = aData4.size()

# �������������
aData = aData1 + aData2 + aData3 + aData4

# ID�ǥ�����
aData.sort!

# 1�Ĥ�ʸ����ˤ���
sOutString = aData.join("\n")

# �ե�����ؽ��Ϥ���
File.open(sWriteFileId, "w") {|io|
  io.puts(sOutString)
}

# ����ID�η����ɽ������
puts("=" * 20)
printf("COM***      : %3d\n", nData1)
printf("COM***_Conf : %3d\n", nData2)
printf("COMa***     : %3d\n", nData3)
printf("NCOM***     : %3d\n", nData4)
puts("-" * 20)
printf("Total       : %3d\n", (nData1 + nData2 + nData3 + nData4))
puts("=" * 20)
printf("Delete tags : %3d\n", aDelTag.size())
if (aDelTag != nil)
  aDelTag.sort!
  puts("-" * 20)
  aDelTag.each{|sDelTag|
    puts(sDelTag)
  }
end
puts("=" * 20)
