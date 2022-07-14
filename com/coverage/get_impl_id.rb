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
#  $Id: get_impl_id.rb 1241 2015-03-25 07:26:02Z panasonic-ayane $
#

#
#  ��������������λ��ͥ�������Ф���
#

if ($0 == __FILE__)
  TOOL_ROOT = File.expand_path(File.dirname(__FILE__) + "/")
  $LOAD_PATH.unshift(TOOL_ROOT)
end

require "pp"

# �񤭽Ф��ե�����
sWriteFileId = File.dirname(__FILE__) + "/com_impl_id.txt"

# �оݥ�����������
aTargetFiles = []
aTargetFiles.push("#{TOOL_ROOT}/../Com.c")
aTargetFiles.push("#{TOOL_ROOT}/../Com.h")
aTargetFiles.push("#{TOOL_ROOT}/../Com.tf")
aTargetFiles.push("#{TOOL_ROOT}/../../general/ComStack_Types.h")

# �оݥ�������ɽ��
TAG_REG_COM = "COM[0-9][0-9][0-9]"
TAG_REG_COM_CONF = "COM[0-9][0-9][0-9]_Conf"
TAG_REG_COMA = "COMa[0-9][0-9][0-9]"
TAG_REG_NCOM = "NCOM[0-9][0-9][0-9]"
TAG_REG_ALL = "N?COMa?[0-9][0-9][0-9][_Conf]*"

#
# �������������ɼ���
#
aCodeData = []
aTargetFiles.each{|sFileName|
  # �ե������ɤ߹���
  sFileData = File.read(sFileName)

  # ���ԥ����ɤ��Ѵ�
  sFileData.gsub!("\r\n","\n")
  sFileData.gsub!("\r","\n")

  aFileData = sFileData.split("\n")

  # [1����Υ����ɡ��Կ����ե�����̾]�Υ��åȤ��ݻ�����
  nLine = 1
  aFileData.each{|sLine|
    aCodeData.push([sLine, nLine, File.basename(sFileName)])
    nLine += 1
  }
}

# �������
hSpecInfo = {}
aCodeData.each{|aLine|
  # ���ͥ�����¸�ߤ��ʤ����ϲ��⤷�ʤ�
  if (aLine[0] !~ /\W#{TAG_REG_ALL}\W/)
    next
  end

  aTags = []
  # 1�Ԥ˴ޤޤ�뤹�٤Ƥλ��ͥ��������
  aTags.concat(aLine[0].scan(/\[#{TAG_REG_ALL}\]/))
  aTags.concat(aLine[0].scan(/\<#{TAG_REG_ALL}\>/))

  aTags.each{|sTag|
    if (!hSpecInfo.has_key?(sTag))
      hSpecInfo[sTag] = []
    end
    hSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# ������̤�ID�ǥ�����
aTags = hSpecInfo.keys
aTags.sort!

#
# ������̤�ե�����ؽ��Ϥ���
#
sResult = ""
aTags.each{|sTag|
  sPlace = ""
  hSpecInfo[sTag].each{|sLine|
    sPlace += "#{sLine}, "
  }
  sPlace.chop!().chop!()

  sResult += "#{sTag} @ #{sPlace}\n"
}

File.open(sWriteFileId, "w") {|io|
  io.puts(sResult)
}

#
# �оݻ��ͤ����оݻ��ͤν�ʣ�����å�
#
aTargetSpec = []
aNonTargetSpec = []
aCodeData.each{|aLine|
  # ���ͥ�����¸�ߤ��ʤ����ϲ��⤷�ʤ�
  if (aLine[0] !~ /\W#{TAG_REG_ALL}\W/)
    next
  end

  # 1�Ԥ˴ޤޤ�뤹�٤Ƥλ��ͥ��������
  aTargetSpec.concat(aLine[0].scan(/\[#{TAG_REG_ALL}\]/))
  aNonTargetSpec.concat(aLine[0].scan(/\<#{TAG_REG_ALL}\>/))
}

aTmp = []
aTargetSpec.each{|sTarget|
  aTmp.push(sTarget.gsub(/\W(#{TAG_REG_ALL})\W/, "\\1"))
}
aTargetSpec = aTmp
aTmp = []
aNonTargetSpec.each{|sNonTarget|
  aTmp.push(sNonTarget.gsub(/\W(#{TAG_REG_ALL})\W/, "\\1"))
}
aNonTargetSpec = aTmp

# ��ʣ���Ƥ����Τ�������ID�ǥ�����
aTargetSpec.uniq!
aNonTargetSpec.uniq!
aTargetSpec.sort!
aNonTargetSpec.sort!

nTargetCom = 0
nTargetComConf = 0
nTargetComA = 0
nTargetNCom = 0
aTargetSpec.each{|sTag|
  if (sTag =~ /^#{TAG_REG_COM}$/)
    nTargetCom = nTargetCom + 1
  elsif (sTag =~ /^#{TAG_REG_COM_CONF}$/)
    nTargetComConf = nTargetComConf + 1
  elsif (sTag =~ /^#{TAG_REG_COMA}$/)
    nTargetComA = nTargetComA + 1
  elsif (sTag =~ /^#{TAG_REG_NCOM}$/)
    nTargetNCom = nTargetNCom + 1
  else
    abort("Error!!")
  end
}

# ���ݡ����о�/���оݤη��ɽ��
puts("=" * 35)
puts("All tags             : #{aTargetSpec.size() + aNonTargetSpec.size()}")
puts("-" * 35)
fRatio = aTargetSpec.size().to_f() / aTags.size().to_f * 100
puts("For support tags     : #{aTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
fRatio = aNonTargetSpec.size().to_f() / aTags.size().to_f * 100
puts("For non-support tags : #{aNonTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
puts("=" * 35)

# ���ݡ����оݤξܺ�ɽ��
puts("For support tags     : #{aTargetSpec.size()}")
puts("-" * 35)
fRatio = nTargetCom.to_f() / aTargetSpec.size().to_f() * 100
printf("COM***               : %3d (%0.1f%%)\n", nTargetCom, fRatio)
fRatio = nTargetComConf.to_f() / aTargetSpec.size().to_f() * 100
printf("COM***_Conf          : %3d (%0.1f%%)\n", nTargetComConf, fRatio)
fRatio = nTargetComA.to_f() / aTargetSpec.size().to_f() * 100
printf("COMa***              : %3d (%0.1f%%)\n", nTargetComA, fRatio)
fRatio = nTargetNCom.to_f() / aTargetSpec.size().to_f() * 100
printf("NCOM***              : %3d (%0.1f%%)\n", nTargetNCom, fRatio)
puts("=" * 35)

# ��ʣ����������ɽ��
aTargetSpec.each{|sTarget|
  if (aNonTargetSpec.include?(sTarget))
    puts("#{sTarget} is conflicted !!")
    pp hSpecInfo["[#{sTarget}]"]
    pp hSpecInfo["<#{sTarget}>"]
  end
}
