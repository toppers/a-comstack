#!ruby -Ke
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
aTargetFiles.push("#{TOOL_ROOT}/../../CanIf.c")
aTargetFiles.push("#{TOOL_ROOT}/../../CanIf.h")
aTargetFiles.push("#{TOOL_ROOT}/../../CanIf_Types.h")
aTargetFiles.push("#{TOOL_ROOT}/../../canif.tf")

# NCANIF���ͽ�
aNCANIFSpecFiles = []
aNCANIFSpecFiles.push("#{TOOL_ROOT}/../../doc/canif_spec.txt")
aNCANIFSpecFiles.push("#{TOOL_ROOT}/../../doc/canif_container.txt")
aNCANIFSpecFiles.push("#{TOOL_ROOT}/../../doc/canif_system_service.txt")

# �оݥ�������ɽ��
sTagRegNcanif = "NCANIF[0-9][0-9][0-9]"
sTagRegCanIfA = "CANIFa[0-9][0-9][0-9]"
sTagRegCanIf = "CANIFa?[0-9][0-9][0-9][_Conf]*"
sTagRegAll = "N?#{sTagRegCanIf}"

#
# NCANIF��CANIFa���ͼ���
#
aSpecData = []
aNCANIFSpecFiles.each{|sFileName|
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
hNcanifSpecInfo = {}

aSpecData.each{|aLine|
  # ���ͥ�����¸�ߤ��ʤ����ϲ��⤷�ʤ�
  if ((aLine[0] !~ /\[#{sTagRegNcanif}\]/) && (aLine[0] !~ /\[#{sTagRegCanIfA}\]/))
    next
  end

  aTags = []
  # 1�Ԥ˴ޤޤ�뤹�٤Ƥλ��ͥ��������
  aTags.concat(aLine[0].scan(/\[#{sTagRegNcanif}\]/))
  aTags.concat(aLine[0].scan(/\[#{sTagRegCanIfA}\]/))

  aTags.each{|sTag|
    if (!hNcanifSpecInfo.has_key?(sTag))
      hNcanifSpecInfo[sTag] = []
    end
    hNcanifSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# ID�ǥ����Ȥ��Ʒ�̤����
aTagID = hNcanifSpecInfo.keys()
aTagID.sort!()
sResult = ""
aTagID.each{|sTag|
  sPlace = ""
  hNcanifSpecInfo[sTag].each{|sLine|
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
aNcanifSpec = []
aCanIfASpec = []
aTagID.each{|sTag|
  # NCANIF����
  if (sTag =~ /\[#{sTagRegNcanif}\]/)
    aNcanifSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # CANIFa����
  elsif (sTag =~ /\[#{sTagRegCanIfA}\]/)
    aCanIfASpec.push(sTag.gsub(/\[(#{sTagRegCanIfA})\]/, "\\1"))
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
aImplCanIfASpec = []
aImplNcanifSpec = []
aTagID.each{|sTag|
  # CANIFa����
  if (sTag =~ /\[#{sTagRegCanIfA}\]/)
    aImplCanIfASpec.push(sTag.gsub(/\[(#{sTagRegCanIfA})\]/, "\\1"))
  # NCANIF����
  elsif (sTag =~ /\[#{sTagRegNcanif}\]/)
    aImplNcanifSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # �оݻ���
  elsif (sTag =~ /\[#{sTagRegCanIf}\]/)
    aTargetSpec.push(sTag.gsub(/\[(#{sTagRegCanIf})\]/, "\\1"))
    nAutosarCnt += 1
  # ���оݻ���
  elsif (sTag =~ /<#{sTagRegCanIf}>/)
    aNonTargetSpec.push(sTag.gsub(/<(#{sTagRegCanIf})>/, "\\1"))
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
puts("NCANIF tags     : #{aNcanifSpec.size()}")
puts("Implemented tags: #{aImplNcanifSpec.size()}")
fCoverage = aImplNcanifSpec.size().to_f() / aNcanifSpec.size().to_f() * 100
puts("NCANIF Coverage : #{sprintf('%0.1f', fCoverage)} %")
puts("-" * 35)
puts("CANIFa tags     : #{aCanIfASpec.size()}")
puts("Implemented tags: #{aImplCanIfASpec.size()}")
fCoverage = aImplCanIfASpec.size().to_f() / aCanIfASpec.size().to_f() * 100
puts("CANIFa Coverage : #{sprintf('%0.1f', fCoverage)} %")
puts("=" * 35)

# ��������Ƥ��ʤ�������ɽ��
aNcanifSpec.each{|sTag|
  if (!aImplNcanifSpec.include?(sTag))
    puts(sTag)
  end
}
aCanIfASpec.each{|sTag|
  if (!aImplCanIfASpec.include?(sTag))
    puts(sTag)
  end
}

