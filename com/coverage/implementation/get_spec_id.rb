#!ruby -Ke
#
#  TOPPRES/A-COM
#      Automotive COM
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

#
#  ��������������λ��ͥ�������Ф���
#

if ($0 == __FILE__)
  TOOL_ROOT = File.expand_path(File.dirname(__FILE__) + "/")
  $LOAD_PATH.unshift(TOOL_ROOT)
end

require "pp"

# �оݥե�����
aTargetFiles = []
aTargetFiles.push("#{TOOL_ROOT}/../../Com.c")
aTargetFiles.push("#{TOOL_ROOT}/../../Com.h")
aTargetFiles.push("#{TOOL_ROOT}/../../Com.tf")
aTargetFiles.push("#{TOOL_ROOT}/../../../general/ComStack_Types.h")

# NCOM���ͽ�
aNCOMSpecFiles = []
aNCOMSpecFiles.push("#{TOOL_ROOT}/../../doc/com_spec.txt")
aNCOMSpecFiles.push("#{TOOL_ROOT}/../../doc/com_container.txt")
aNCOMSpecFiles.push("#{TOOL_ROOT}/../../doc/com_system_service.txt")

# �оݥ�������ɽ��
sTagRegNcom = "NCOM[0-9][0-9][0-9]"
sTagRegComA = "COMa[0-9][0-9][0-9]"
sTagRegCom = "COMa?[0-9][0-9][0-9][_Conf]*"
sTagRegAll = "N?#{sTagRegCom}"

#
# NCOM��COMa���ͼ���
#
aSpecData = []
aNCOMSpecFiles.each{|sFileName|
  sFileData = File.read(sFileName)
  # ���ԥ����ɤ��Ѵ�
  if (sFileData.include?("\r\n"))
    sFileData.gsub!("\r\n","\n")
  end
  if (sFileData.include?("\r"))
    sFileData.gsub!("\r","\n")
  end

  aTmpData = sFileData.split("\n")

  # [1����Υ����ɡ��Կ����ե�����̾]�Υ��åȤ��ݻ�����
  nLine = 1
  aTmpData.each{|sLine|
    aSpecData.push([sLine, nLine, File.basename(sFileName)])
    nLine += 1
  }
}

# �������
hNcomSpecInfo = {}

aSpecData.each{|aLine|
  # ���ͥ�����¸�ߤ��ʤ����ϲ��⤷�ʤ�
  if ((aLine[0] !~ /\[#{sTagRegNcom}\]/) && (aLine[0] !~ /\[#{sTagRegComA}\]/))
    next
  end

  aTags = []
  # 1�Ԥ˴ޤޤ�뤹�٤Ƥλ��ͥ��������
  aTags.concat(aLine[0].scan(/\[#{sTagRegNcom}\]/))
  aTags.concat(aLine[0].scan(/\[#{sTagRegComA}\]/))

  aTags.each{|sTag|
    if (!hNcomSpecInfo.has_key?(sTag))
      hNcomSpecInfo[sTag] = []
    end
    hNcomSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# ID�ǥ����Ȥ��Ʒ�̤����
aTagID = hNcomSpecInfo.keys()
aTagID.sort!()
sResult = ""
aTagID.each{|sTag|
  sPlace = ""
  hNcomSpecInfo[sTag].each{|sLine|
    sPlace += "#{sLine}, "
  }
  sPlace.chop!().chop!()

  sResult += "#{sTag} @ #{sPlace}\n"
}

# �ե�����ؽ��Ϥ���
File.open("#{TOOL_ROOT}/nces_spec_id.txt", "w") {|io|
  io.puts(sResult)
}

# �оݻ��ͤ����оݻ��ͤν�ʣ�����å�
aNcomSpec = []
aComASpec = []
aTagID.each{|sTag|
  # NCOM����
  if (sTag =~ /\[#{sTagRegNcom}\]/)
    aNcomSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # COMa����
  elsif (sTag =~ /\[#{sTagRegComA}\]/)
    aComASpec.push(sTag.gsub(/\[(#{sTagRegComA})\]/, "\\1"))
  else
    abort("Error!!")
  end
}



#
# �������������ɼ���
#
aCodeData = []
aTargetFiles.each{|sFileName|
  sFileData = File.read(sFileName)
  # ���ԥ����ɤ��Ѵ�
  if (sFileData.include?("\r\n"))
    sFileData.gsub!("\r\n","\n")
  end
  if (sFileData.include?("\r"))
    sFileData.gsub!("\r","\n")
  end

  aTmpData = sFileData.split("\n")

  # [1����Υ����ɡ��Կ����ե�����̾]�Υ��åȤ��ݻ�����
  nLine = 1
  aTmpData.each{|sLine|
    aCodeData.push([sLine, nLine, File.basename(sFileName)])
    nLine += 1
  }
}

# �������
hSpecInfo = {}

aCodeData.each{|aLine|
  # ���ͥ�����¸�ߤ��ʤ����ϲ��⤷�ʤ�
  if (aLine[0] !~ /[\[<]#{sTagRegAll}[\]>]/)
    next
  end

  aTags = []
  # 1�Ԥ˴ޤޤ�뤹�٤Ƥλ��ͥ��������
  aTags.concat(aLine[0].scan(/[\[<]#{sTagRegAll}[\]>]/))

  aTags.each{|sTag|
    if (!hSpecInfo.has_key?(sTag))
      hSpecInfo[sTag] = []
    end
    hSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# ID�ǥ����Ȥ��Ʒ�̤����
aTagID = hSpecInfo.keys()
aTagID.sort!()
sResult = ""
aTagID.each{|sTag|
  sPlace = ""
  hSpecInfo[sTag].each{|sLine|
    sPlace += "#{sLine}, "
  }
  sPlace.chop!().chop!()

  sResult += "#{sTag} @ #{sPlace}\n"
}

# �ե�����ؽ��Ϥ���
File.open("#{TOOL_ROOT}/impl_spec_id.txt", "w") {|io|
  io.puts(sResult)
}

# �оݻ��ͤ����оݻ��ͤν�ʣ�����å�
nAutosarCnt = 0
aTargetSpec = []
aNonTargetSpec = []
aImplComASpec = []
aImplNcomSpec = []
aTagID.each{|sTag|
  # COMa����
  if (sTag =~ /\[#{sTagRegComA}\]/)
    aImplComASpec.push(sTag.gsub(/\[(#{sTagRegComA})\]/, "\\1"))
  # NCOM����
  elsif (sTag =~ /\[#{sTagRegNcom}\]/)
    aImplNcomSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # �оݻ���
  elsif (sTag =~ /\[#{sTagRegCom}\]/)
    aTargetSpec.push(sTag.gsub(/\[(#{sTagRegCom})\]/, "\\1"))
    nAutosarCnt += 1
  # ���оݻ���
  elsif (sTag =~ /<#{sTagRegCom}>/)
    aNonTargetSpec.push(sTag.gsub(/<(#{sTagRegCom})>/, "\\1"))
    nAutosarCnt += 1
  else
    abort("Error!!")
  end
}

# ���ݡ����о�/���оݤη��ɽ��
puts("=" * 35)
puts("AUTOSAR tags         : #{aTargetSpec.size() + aNonTargetSpec.size()}")
puts("-" * 35)
fRatio = aTargetSpec.size().to_f() / nAutosarCnt * 100
puts("For support tags     : #{aTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
fRatio = aNonTargetSpec.size().to_f() / nAutosarCnt * 100
puts("For non-support tags : #{aNonTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
puts("=" * 35)

# ��ʣ����������ɽ��
aTargetSpec.each{|sTarget|
  if (aNonTargetSpec.include?(sTarget))
    puts("#{sTarget} is conflicted !!")
    pp hSpecInfo["[#{sTarget}]"]
    pp hSpecInfo["<#{sTarget}>"]
  end
}

# �ȼ������η��ɽ��
puts("=" * 35)
puts("NCOM tags       : #{aNcomSpec.size()}")
puts("Implemented tags: #{aImplNcomSpec.size()}")
fCoverage = aImplNcomSpec.size().to_f() / aNcomSpec.size().to_f() * 100
puts("NCOM Coverage   : #{sprintf('%0.1f', fCoverage)} %")
puts("-" * 35)
puts("COMa tags       : #{aComASpec.size()}")
puts("Implemented tags: #{aImplComASpec.size()}")
fCoverage = aImplComASpec.size().to_f() / aComASpec.size().to_f() * 100
puts("COMa Coverage   : #{sprintf('%0.1f', fCoverage)} %")
puts("=" * 35)

# ��������Ƥ��ʤ�������ɽ��
aNcomSpec.each{|sTag|
  if (!aImplNcomSpec.include?(sTag))
    puts(sTag)
  end
}
aComASpec.each{|sTag|
  if (!aImplComASpec.include?(sTag))
    puts(sTag)
  end
}

