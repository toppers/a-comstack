#!ruby -Ks
#
#  TOPPRES/A-CANIF
#      Automotive CANIF
#
#  Copyright (C) 2013-2014 by Center for Embedded Computing Systems
#              Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
#  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
#  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
#  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
#  Copyright (C) 2013-2014 by TOSHIBA CORPORATION, JAPAN
#  Copyright (C) 2013-2014 by Witz Corporation, JAPAN
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
#  $Id: get_spec_id.rb 425 2014-09-17 00:46:01Z fsi-dankei $
#

#=====================================================================
# �ƥ����ȥե�����(AUTOSAR_SWS_CANInterface_R4.0.3.txt)���顤CANIF�˴�
# ������ͥ�����ȴ���Ф��ơ�ID������ե�����ؽ��Ϥ���
# ���ƥ����ȥե�����ϡ�PDF�ե������Adobe Reader�����Ѵ���ǽ����Ѥ��ơ�
#   ��������
#=====================================================================

# �񤭽Ф��ե�����
sWriteFileId = File.dirname(__FILE__) + "/autosar_spec_id.txt"

# pdf�����ɤ߽Ф����ƥ����ȥǡ���
sTextFile = "AUTOSAR_SWS_CANInterface_R4.0.3.txt"

# �ƥ����ȥե�������ɤ߹���
sText = File.read(sTextFile)

# ���Ԥ���(����������ǲ��Ԥ����륱�����б�)
sText.gsub!("\r\n", "")
sText.gsub!("\r", "")
sText.gsub!("\n", "")

# �оݥ����򸡺�����
aData1 = sText.scan(/\[CANIF[0-9][0-9][0-9]\]/) + sText.scan(/CANIF[0-9][0-9][0-9]:\s/)
aData2 = sText.scan(/CANIF[0-9][0-9][0-9]_Conf\s:/)
nData1 = aData1.size()
nData2 = aData2.size()

# CANIF794�������쥮��顼�ե����ޥåȤʤΤǼ�ư���ɲä���
aTags = aData1 + aData2 + ["CANIF794"]

aData = []
aDup = []

# :,[,]����
aTags.each{|sLine|
  sTemp = sLine.gsub(/:|\s|\[|\]/, "")
  # ��ʣ���Ƥ����Τ�2�٤���ʤ�
  if (aData.include?(sTemp))
    aDup.push(sTemp)
  else
    aData.push(sTemp)
  end
}

# CANIF484�Ϻ�����ͤʤΤǺ������
aData.delete("CANIF484")

# ID�ǥ�����
aData.sort!

# 1�Ĥ�ʸ����ˤ���
sOutString = aData.join("\n")

# �ե�����ؽ��Ϥ���
File.open(sWriteFileId, "w") {|io|
  io.puts(sOutString)
}

# ����ID�η����ɽ������
print("================================\n")
printf("CANIF***      : %3d\n", nData1)
printf("CANIF***_Conf : %3d\n", nData2)
print("================================\n")
printf("Total         : %3d\n", (nData1 + nData2))

# ��ʣ����ID��¸�ߤ������ɽ������
if (aDup.size != 0)
  aDup.sort!
  print("--------------------------------\n")
  print("the following IDs are duplicated\n")
  print("--------------------------------\n")
  aDup.each{|sLine|
    print(sLine + "\n")
  }
end
