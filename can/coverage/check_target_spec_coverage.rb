#!ruby -Ke
#
#  TOPPRES/A-CAN
#      Automotive CAN
#
#  Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
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
#  $Id: check_target_spec_coverage.rb 599 2014-10-17 01:27:58Z shigihara $
#

#
#  �ޥ������¸���Υ�������������λ��ͥ�������Ф���
#

if ($0 == __FILE__)
  TOOL_ROOT = File.expand_path(File.dirname(__FILE__) + "/")
  $LOAD_PATH.unshift(TOOL_ROOT)
end

require "pp"

# ���¸�����Ͱ����ե�����
sNonDependSpecFile = "#{TOOL_ROOT}/implementation/impl_spec_id.txt"

# ��¸���оݥե�����ǡ���
hTargetFiles = {"hsbv850e2fg4_cx" => ["#{TOOL_ROOT}/../arch/v850e2/Can_Prc.h", "#{TOOL_ROOT}/../arch/v850e2/Can_Prc.tf"],
                "nios2_dev_gcc" => []}
hTargetFiles.each{|sName, aFiles|
  aFiles.push("#{TOOL_ROOT}/../target/#{sName}/Can_Irq.c")
  aFiles.push("#{TOOL_ROOT}/../target/#{sName}/Can_Target.h")
  aFiles.push("#{TOOL_ROOT}/../target/#{sName}/Can_Target.tf")
}

# ��¸���������Ͱ�������
sFileData = File.read(sNonDependSpecFile)
aDependSpec = sFileData.scan(/\((CAN[0-9][0-9][0-9])\)/).flatten()

# ��¸����˥���������å�
hTargetFiles.each{|sName, aFiles|
  puts("===== #{sName} =====")

  aTargetSpec = []
  aFiles.each{|sFile|
    sFileData = File.read(sFile)
    aTargetSpec.concat(sFileData.scan(/[\[<](CAN[0-9][0-9][0-9])[>\]]/).flatten())
  }

  bChk = false
  nCnt = 0
  aDependSpec.each{|sSpecID|
    if (!aTargetSpec.include?(sSpecID))
      puts(sSpecID)
      nCnt += 1
      bChk = true
    end
  }

  if (bChk == false)
    puts("All spec-id : OK !\n\n")
  else
    puts("-" * 30)
    puts("Above spec-ids(#{nCnt}) are not found !\n\n")
  end
}
