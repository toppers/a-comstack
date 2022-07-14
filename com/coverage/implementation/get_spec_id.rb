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
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
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
#  $Id: get_spec_id.rb 425 2014-09-17 00:46:01Z fsi-dankei $
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
aTargetFiles.push("#{TOOL_ROOT}/../../Com.c")
aTargetFiles.push("#{TOOL_ROOT}/../../Com.h")
aTargetFiles.push("#{TOOL_ROOT}/../../Com.tf")
aTargetFiles.push("#{TOOL_ROOT}/../../../general/ComStack_Types.h")

# NCOM仕様書
aNCOMSpecFiles = []
aNCOMSpecFiles.push("#{TOOL_ROOT}/../../doc/com_spec.txt")
aNCOMSpecFiles.push("#{TOOL_ROOT}/../../doc/com_container.txt")
aNCOMSpecFiles.push("#{TOOL_ROOT}/../../doc/com_system_service.txt")

# 対象タグ正規表現
sTagRegNcom = "NCOM[0-9][0-9][0-9]"
sTagRegComA = "COMa[0-9][0-9][0-9]"
sTagRegCom = "COMa?[0-9][0-9][0-9][_Conf]*"
sTagRegAll = "N?#{sTagRegCom}"

#
# NCOM，COMa仕様収集
#
aSpecData = []
aNCOMSpecFiles.each{|sFileName|
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
hNcomSpecInfo = {}

aSpecData.each{|aLine|
  # 仕様タグが存在しない場合は何もしない
  if ((aLine[0] !~ /\[#{sTagRegNcom}\]/) && (aLine[0] !~ /\[#{sTagRegComA}\]/))
    next
  end

  aTags = []
  # 1行に含まれるすべての仕様タグを抽出
  aTags.concat(aLine[0].scan(/\[#{sTagRegNcom}\]/))
  aTags.concat(aLine[0].scan(/\[#{sTagRegComA}\]/))

  aTags.each{|sTag|
    if (!hNcomSpecInfo.has_key?(sTag))
      hNcomSpecInfo[sTag] = []
    end
    hNcomSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# IDでソートして結果を作成
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

# ファイルへ出力する
File.open("#{TOOL_ROOT}/nces_spec_id.txt", "w") {|io|
  io.puts(sResult)
}

# 対象仕様と非対象仕様の重複チェック
aNcomSpec = []
aComASpec = []
aTagID.each{|sTag|
  # NCOM仕様
  if (sTag =~ /\[#{sTagRegNcom}\]/)
    aNcomSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # COMa仕様
  elsif (sTag =~ /\[#{sTagRegComA}\]/)
    aComASpec.push(sTag.gsub(/\[(#{sTagRegComA})\]/, "\\1"))
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
aImplComASpec = []
aImplNcomSpec = []
aTagID.each{|sTag|
  # COMa仕様
  if (sTag =~ /\[#{sTagRegComA}\]/)
    aImplComASpec.push(sTag.gsub(/\[(#{sTagRegComA})\]/, "\\1"))
  # NCOM仕様
  elsif (sTag =~ /\[#{sTagRegNcom}\]/)
    aImplNcomSpec.push(sTag.gsub(/\[(#{sTagRegAll})\]/, "\\1"))
  # 対象仕様
  elsif (sTag =~ /\[#{sTagRegCom}\]/)
    aTargetSpec.push(sTag.gsub(/\[(#{sTagRegCom})\]/, "\\1"))
    nAutosarCnt += 1
  # 非対象仕様
  elsif (sTag =~ /<#{sTagRegCom}>/)
    aNonTargetSpec.push(sTag.gsub(/<(#{sTagRegCom})>/, "\\1"))
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

# 実装されていないかタグ表示
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

