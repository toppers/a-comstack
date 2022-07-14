#!ruby -Ke
#
#  TOPPRES/A-CAN
#      Automotive CAN
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
#  $Id: get_spec_id.rb 599 2014-10-17 01:27:58Z shigihara $
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
aTargetFiles.push("#{TOOL_ROOT}/../../Can.c")
aTargetFiles.push("#{TOOL_ROOT}/../../Can.h")
aTargetFiles.push("#{TOOL_ROOT}/../../Can_GeneralTypes.h")
aTargetFiles.push("#{TOOL_ROOT}/../../can.tf")

# NCAN���ͽ�
aNCANSpecFiles = []
aNCANSpecFiles.push("#{TOOL_ROOT}/../../doc/can_spec.txt")

# �оݥ�������ɽ��
sTagRegNcan = "NCAN[0-9][0-9][0-9]"
sTagRegCanA = "CANa[0-9][0-9][0-9]"
sTagRegCan = "CANa?[0-9][0-9][0-9][_Conf]*"
sTagRegAll = "N?#{sTagRegCan}"

#
# NCAN��CANa���ͼ���
#
aSpecData = []
aNCANSpecFiles.each{|sFileName|
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
hNcanSpecInfo = {}

aSpecData.each{|aLine|
  # ���ͥ�����¸�ߤ��ʤ����ϲ��⤷�ʤ�
  if ((aLine[0] !~ /\[#{sTagRegNcan}\]/) && (aLine[0] !~ /\[#{sTagRegCanA}\]/))
    next
  end

  aTags = []
  # 1�Ԥ˴ޤޤ�뤹�٤Ƥλ��ͥ��������
  aTags.concat(aLine[0].scan(/\[#{sTagRegNcan}\]/))
  aTags.concat(aLine[0].scan(/\[#{sTagRegCanA}\]/))

  aTags.each{|sTag|
    if (!hNcanSpecInfo.has_key?(sTag))
      hNcanSpecInfo[sTag] = []
    end
    hNcanSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# ID�ǥ����Ȥ��Ʒ�̤����
aTagID = hNcanSpecInfo.keys()
aTagID.sort!()
sResult = ""
aTagID.each{|sTag|
  sPlace = ""
  hNcanSpecInfo[sTag].each{|sLine|
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
aNcanSpec = []
aCanASpec = []
aTagID.each{|sTag|
  # NCAN����
  if (sTag =~ /\[#{sTagRegNcan}\]/)
    aNcanSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # CANa����
  elsif (sTag =~ /\[#{sTagRegCanA}\]/)
    aCanASpec.push(sTag.gsub(/\[(#{sTagRegCanA})\]/, "\\1"))
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
  if (aLine[0] !~ /[\[<\(]#{sTagRegAll}[\]>\)]/)
    next
  end

  aTags = []
  # 1�Ԥ˴ޤޤ�뤹�٤Ƥλ��ͥ��������
  aTags.concat(aLine[0].scan(/[\[<\(]#{sTagRegAll}[\]>\)]/))

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
aImplCanASpec = []
aImplNcanSpec = []
aDependCanSpec = []
aTagID.each{|sTag|
  # CANa����
  if (sTag =~ /\[#{sTagRegCanA}\]/)
    aImplCanASpec.push(sTag.gsub(/\[(#{sTagRegCanA})\]/, "\\1"))
  # NCAN����
  elsif (sTag =~ /\[#{sTagRegNcan}\]/)
    aImplNcanSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # �оݻ���
  elsif (sTag =~ /\[#{sTagRegCan}\]/)
    aTargetSpec.push(sTag.gsub(/\[(#{sTagRegCan})\]/, "\\1"))
    nAutosarCnt += 1
  # ���оݻ���
  elsif (sTag =~ /<#{sTagRegCan}>/)
    aNonTargetSpec.push(sTag.gsub(/<(#{sTagRegCan})>/, "\\1"))
    nAutosarCnt += 1
  # ��¸������
  elsif (sTag =~ /\(#{sTagRegCan}\)/)
    aDependCanSpec.push(sTag.gsub(/\((#{sTagRegCan})\)/, "\\1"))
    nAutosarCnt += 1
  else
    abort("Error!!")
  end
}

# ���ݡ����о�/���оݤη��ɽ��
puts("=" * 35)
puts("AUTOSAR tags         : #{nAutosarCnt}")
puts("-" * 35)
fRatio = aTargetSpec.size().to_f() / nAutosarCnt * 100
puts("For support tags     : #{aTargetSpec.size() + aDependCanSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
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
  if (aDependCanSpec.include?(sTarget))
    puts("#{sTarget} is conflicted !!")
    pp hSpecInfo["[#{sTarget}]"]
    pp hSpecInfo["(#{sTarget})"]
  end
}

# �ȼ������η��ɽ��
puts("=" * 35)
puts("NCAN tags       : #{aNcanSpec.size()}")
puts("Implemented tags: #{aImplNcanSpec.size()}")
fCoverage = aImplNcanSpec.size().to_f() / aNcanSpec.size().to_f() * 100
puts("NCAN Coverage   : #{sprintf('%0.1f', fCoverage)} %")
puts("-" * 35)
puts("CANa tags       : #{aCanASpec.size()}")
puts("Implemented tags: #{aImplCanASpec.size()}")
fCoverage = aImplCanASpec.size().to_f() / aCanASpec.size().to_f() * 100
puts("CANa Coverage   : #{sprintf('%0.1f', fCoverage)} %")
puts("=" * 35)

# ��������Ƥ��ʤ�����ɽ��
aNcanSpec.each{|sTag|
  if (!aImplNcanSpec.include?(sTag))
    puts(sTag)
  end
}
aCanASpec.each{|sTag|
  if (!aImplCanASpec.include?(sTag))
    puts(sTag)
  end
}

