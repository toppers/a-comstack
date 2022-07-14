#!ruby -Ku
#
#  TOPPRES/A-CANTP
#      Automotive CANTP
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
#  $Id: get_test_id.rb 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
#

#
#  ソースコード中の仕様タグを抽出する
#

if ($0 == __FILE__)
  TOOL_ROOT = File.expand_path(File.dirname(__FILE__) + "/")
  $LOAD_PATH.unshift(TOOL_ROOT)
end

require "pp"

# 書き出すファイル
sWriteFileId = File.dirname(__FILE__) + "/cantp_test_id.txt"

# pdfから読み出したテキストデータ
aTargetFiles = []
aTargetFiles.push("cantp_test.txt")

# 対象タグ正規表現
TAG_REG_SWS_CANTP = "SWS_CanTp_[0-9][0-9][0-9][0-9][0-9]"
TAG_REG_ECUC_CANTP = "ECUC_CanTp_[0-9][0-9][0-9][0-9][0-9]"
TAG_REG_SWS_CANTPA = "SWS_CanTpa_[0-9][0-9][0-9][0-9][0-9]"
TAG_REG_ECUC_CANTPA = "ECUC_CanTpa_[0-9][0-9][0-9][0-9][0-9]"
TAG_REG_NCANTP = "NCanTp_[0-9][0-9][0-9][0-9][0-9]"
TAG_REG_ALL = "[SWS_]*[ECUC_]*[N]*CanTpa?_[0-9][0-9][0-9][0-9][0-9]"

#
# 全ソースコード収集
#
aCodeData = []
aTargetFiles.each{|sFileName|
  # ファイル読み込み
  sFileData = File.read(sFileName)

  # 改行コードを変換
  sFileData.gsub!("\r\n","\n")
  sFileData.gsub!("\r","\n")

  aFileData = sFileData.split("\n")

  # [1行毎のコード，行数，ファイル名]のセットで保持する
  nLine = 1
  aFileData.each{|sLine|
    aCodeData.push([sLine, nLine, File.basename(sFileName)])
    nLine += 1
  }
}

# 取得結果
hSpecInfo = {}
aCodeData.each{|aLine|
  # 仕様タグが存在しない場合は何もしない
  if (aLine[0] !~ /\W#{TAG_REG_ALL}\W/)
    next
  end

  aTags = []
  # 1行に含まれるすべての仕様タグを抽出
  aTags.concat(aLine[0].scan(/\[#{TAG_REG_ALL}\]/))
  aTags.concat(aLine[0].scan(/\<#{TAG_REG_ALL}\>/))

  aTags.each{|sTag|
    if (!hSpecInfo.has_key?(sTag))
      hSpecInfo[sTag] = []
    end
    hSpecInfo[sTag].push("#{aLine[2]}:#{aLine[1]}")
  }
}

# 取得結果をIDでソート
aTags = hSpecInfo.keys
aTags.sort!

#
# 取得結果をファイルへ出力する
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
# 対象仕様と非対象仕様の重複チェック
#
aTargetSpec = []
aNonTargetSpec = []
aCodeData.each{|aLine|
  # 仕様タグが存在しない場合は何もしない
  if (aLine[0] !~ /\W#{TAG_REG_ALL}\W/)
    next
  end

  # 1行に含まれるすべての仕様タグを抽出
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

# 重複しているものを削除し，IDでソート
aTargetSpec.uniq!
aNonTargetSpec.uniq!
aTargetSpec.sort!
aNonTargetSpec.sort!

nTargetSwsCanTp = 0
nTargetEcucCanTp = 0
nTargetSwsCanTpA = 0
nTargetEcucCanTpA = 0
nTargetNCanTp = 0
aTargetSpec.each{|sTag|
  if (sTag =~ /^#{TAG_REG_SWS_CANTP}$/)
    nTargetSwsCanTp = nTargetSwsCanTp + 1
  elsif (sTag =~ /^#{TAG_REG_ECUC_CANTP}$/)
    nTargetEcucCanTp = nTargetEcucCanTp + 1
  elsif (sTag =~ /^#{TAG_REG_SWS_CANTPA}$/)
    nTargetSwsCanTpA = nTargetSwsCanTpA + 1
  elsif (sTag =~ /^#{TAG_REG_ECUC_CANTPA}$/)
    nTargetEcucCanTpA = nTargetEcucCanTpA + 1
  elsif (sTag =~ /^#{TAG_REG_NCANTP}$/)
    nTargetNCanTp = nTargetNCanTp + 1
  else
    abort("Error!!")
  end
}

# サポート対象/非対象の件数表示
puts("=" * 35)
puts("All tags             : #{aTargetSpec.size() + aNonTargetSpec.size()}")
puts("-" * 35)
fRatio = aTargetSpec.size().to_f() / aTags.size().to_f * 100
puts("For support tags     : #{aTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
fRatio = aNonTargetSpec.size().to_f() / aTags.size().to_f * 100
puts("For non-support tags : #{aNonTargetSpec.size()} (#{sprintf('%0.1f', fRatio)}%)")
puts("=" * 35)

# サポート対象の詳細表示
puts("For support tags     : #{aTargetSpec.size()}")
puts("-" * 35)
fRatio = nTargetSwsCanTp.to_f() / aTargetSpec.size().to_f() * 100
printf("SWS_CanTp_*****    : %3d (%0.1f%%)\n", nTargetSwsCanTp, fRatio)
fRatio = nTargetEcucCanTp.to_f() / aTargetSpec.size().to_f() * 100
printf("ECUC_CanTp_*****   : %3d (%0.1f%%)\n", nTargetEcucCanTp, fRatio)
fRatio = nTargetSwsCanTpA.to_f() / aTargetSpec.size().to_f() * 100
printf("SWS_CanTpa_*****   : %3d (%0.1f%%)\n", nTargetSwsCanTpA, fRatio)
fRatio = nTargetEcucCanTpA.to_f() / aTargetSpec.size().to_f() * 100
printf("ECUC_CanTpa_*****  : %3d (%0.1f%%)\n", nTargetEcucCanTpA, fRatio)
fRatio = nTargetNCanTp.to_f() / aTargetSpec.size().to_f() * 100
printf("NCanTp_*****       : %3d (%0.1f%%)\n", nTargetNCanTp, fRatio)
puts("=" * 35)

# 重複したタグを表示
aTargetSpec.each{|sTarget|
  if (aNonTargetSpec.include?(sTarget))
    puts("#{sTarget} is conflicted !!")
    pp hSpecInfo["[#{sTarget}]"]
    pp hSpecInfo["<#{sTarget}>"]
  end
}
