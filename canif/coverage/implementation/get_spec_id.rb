#!ruby -Ke
#
#  TOPPRES/A-CANIF
#      Automotive CANIF
#
#  Copyright (C) 2013-2016 by Center for Embedded Computing Systems
#                             Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2014-2016 by AISIN COMCRUISE Co., Ltd., JAPAN
#  Copyright (C) 2015-2016 by eSOL Co.,Ltd., JAPAN
#  Copyright (C) 2013-2016 by FUJI SOFT INCORPORATED, JAPAN
#  Copyright (C) 2014-2016 by NEC Communication Systems, Ltd., JAPAN
#  Copyright (C) 2013-2016 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
#  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
#  Copyright (C) 2014-2016 by SCSK Corporation, JAPAN
#  Copyright (C) 2013-2016 by Sunny Giken Inc., JAPAN
#  Copyright (C) 2015-2016 by SUZUKI MOTOR CORPORATION
#  Copyright (C) 2013-2016 by TOSHIBA CORPORATION, JAPAN
#  Copyright (C) 2013-2016 by Witz Corporation
#
#  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
#
#  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
#  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
#  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
#  用する者に対して，AUTOSARパートナーになることを求めている．
#
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
#
#  $Id: get_spec_id.rb 2995 2016-03-02 02:05:09Z fsi-kaitori $
#

#
#  ソースコード中の仕様タグを抽出する
#

if ($0 == __FILE__)
  TOOL_ROOT = File.expand_path(File.dirname(__FILE__) + "/")
  $LOAD_PATH.unshift(TOOL_ROOT)
end

require "pp"

# 対象ファイル
aTargetFiles = []
aTargetFiles.push("#{TOOL_ROOT}/../../CanIf.c")
aTargetFiles.push("#{TOOL_ROOT}/../../CanIf.h")
aTargetFiles.push("#{TOOL_ROOT}/../../CanIf_Types.h")
aTargetFiles.push("#{TOOL_ROOT}/../../canif.tf")

# NCANIF仕様書
aNCANIFSpecFiles = []
aNCANIFSpecFiles.push("#{TOOL_ROOT}/../../doc/canif_spec.txt")
aNCANIFSpecFiles.push("#{TOOL_ROOT}/../../doc/canif_container.txt")
aNCANIFSpecFiles.push("#{TOOL_ROOT}/../../doc/canif_system_service.txt")

# 対象タグ正規表現
sTagRegNcanif = "NCANIF[0-9][0-9][0-9]"
sTagRegCanIfA = "CANIFa[0-9][0-9][0-9]"
sTagRegCanIf = "CANIFa?[0-9][0-9][0-9][_Conf]*"
sTagRegAll = "N?#{sTagRegCanIf}"

#
# NCANIF，CANIFa仕様収集
#
aSpecData = []
aNCANIFSpecFiles.each{|sFileName|
  sFileData = File.read(sFileName)
  # 改行コードを変換
  if (sFileData.include?("\r\n"))
    sFileData.gsub!("\r\n","\n")
  end
  if (sFileData.include?("\r"))
    sFileData.gsub!("\r","\n")
  end

  aTmpData = sFileData.split("\n")

  # [1行毎のコード，行数，ファイル名]のセットで保持する
  nLine = 1
  aTmpData.each{|sLine|
    aSpecData.push([sLine, nLine, File.basename(sFileName)])
    nLine += 1
  }
}

# 取得結果
hNcanifSpecInfo = {}

aSpecData.each{|aLine|
  # 仕様タグが存在しない場合は何もしない
  if ((aLine[0] !~ /\[#{sTagRegNcanif}\]/) && (aLine[0] !~ /\[#{sTagRegCanIfA}\]/))
    next
  end

  aTags = []
  # 1行に含まれるすべての仕様タグを抽出
  aTags.concat(aLine[0].scan(/\[#{sTagRegNcanif}\]/))
  aTags.concat(aLine[0].scan(/\[#{sTagRegCanIfA}\]/))

  aTags.each{|sTag|
    if (!hNcanifSpecInfo.has_key?(sTag))
      hNcanifSpecInfo[sTag] = []
    end
    hNcanifSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# IDでソートして結果を作成
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

# ファイルへ出力する
File.open("#{TOOL_ROOT}/nces_spec_id.txt", "w") {|io|
  io.puts(sResult)
}

# 対象仕様と非対象仕様の重複チェック
aNcanifSpec = []
aCanIfASpec = []
aTagID.each{|sTag|
  # NCANIF仕様
  if (sTag =~ /\[#{sTagRegNcanif}\]/)
    aNcanifSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # CANIFa仕様
  elsif (sTag =~ /\[#{sTagRegCanIfA}\]/)
    aCanIfASpec.push(sTag.gsub(/\[(#{sTagRegCanIfA})\]/, "\\1"))
  else
    abort("Error!!")
  end
}



#
# 全ソースコード収集
#
aCodeData = []
aTargetFiles.each{|sFileName|
  sFileData = File.read(sFileName)
  # 改行コードを変換
  if (sFileData.include?("\r\n"))
    sFileData.gsub!("\r\n","\n")
  end
  if (sFileData.include?("\r"))
    sFileData.gsub!("\r","\n")
  end

  aTmpData = sFileData.split("\n")

  # [1行毎のコード，行数，ファイル名]のセットで保持する
  nLine = 1
  aTmpData.each{|sLine|
    aCodeData.push([sLine, nLine, File.basename(sFileName)])
    nLine += 1
  }
}

# 取得結果
hSpecInfo = {}

aCodeData.each{|aLine|
  # 仕様タグが存在しない場合は何もしない
  if (aLine[0] !~ /[\[<]#{sTagRegAll}[\]>]/)
    next
  end

  aTags = []
  # 1行に含まれるすべての仕様タグを抽出
  aTags.concat(aLine[0].scan(/[\[<]#{sTagRegAll}[\]>]/))

  aTags.each{|sTag|
    if (!hSpecInfo.has_key?(sTag))
      hSpecInfo[sTag] = []
    end
    hSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# IDでソートして結果を作成
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

# ファイルへ出力する
File.open("#{TOOL_ROOT}/impl_spec_id.txt", "w") {|io|
  io.puts(sResult)
}

# 対象仕様と非対象仕様の重複チェック
nAutosarCnt = 0
aTargetSpec = []
aNonTargetSpec = []
aImplCanIfASpec = []
aImplNcanifSpec = []
aTagID.each{|sTag|
  # CANIFa仕様
  if (sTag =~ /\[#{sTagRegCanIfA}\]/)
    aImplCanIfASpec.push(sTag.gsub(/\[(#{sTagRegCanIfA})\]/, "\\1"))
  # NCANIF仕様
  elsif (sTag =~ /\[#{sTagRegNcanif}\]/)
    aImplNcanifSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # 対象仕様
  elsif (sTag =~ /\[#{sTagRegCanIf}\]/)
    aTargetSpec.push(sTag.gsub(/\[(#{sTagRegCanIf})\]/, "\\1"))
    nAutosarCnt += 1
  # 非対象仕様
  elsif (sTag =~ /<#{sTagRegCanIf}>/)
    aNonTargetSpec.push(sTag.gsub(/<(#{sTagRegCanIf})>/, "\\1"))
    nAutosarCnt += 1
  else
    abort("Error!!")
  end
}

# サポート対象/非対象の件数表示
puts("=" * 35)
puts("AUTOSAR tags         : #{aTargetSpec.size() + aNonTargetSpec.size()}")
puts("-" * 35)
fRatio = aTargetSpec.size().to_f() / nAutosarCnt * 100
puts("For support tags     : #{aTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
fRatio = aNonTargetSpec.size().to_f() / nAutosarCnt * 100
puts("For non-support tags : #{aNonTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
puts("=" * 35)

# 重複したタグを表示
aTargetSpec.each{|sTarget|
  if (aNonTargetSpec.include?(sTarget))
    puts("#{sTarget} is conflicted !!")
    pp hSpecInfo["[#{sTarget}]"]
    pp hSpecInfo["<#{sTarget}>"]
  end
}

# 独自タグの件数表示
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

# 実装されていないかタグ表示
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

