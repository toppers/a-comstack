
	TOPPRES/A-COM 仕様カバレッジチェックツール実行手順

本ドキュメントは，TOPPRES/A-COMの仕様カバレッジチェックツールを実行する
手順を示す．

----------------------------------------------------------------------
TOPPRES/A-COM
    Automotive COM

Copyright (C) 2013-2016 by Center for Embedded Computing Systems
                           Graduate School of Information Science, Nagoya Univ., JAPAN
Copyright (C) 2014-2016 by AISIN COMCRUISE Co., Ltd., JAPAN
Copyright (C) 2015-2016 by eSOL Co.,Ltd., JAPAN
Copyright (C) 2013-2016 by FUJI SOFT INCORPORATED, JAPAN
Copyright (C) 2014-2016 by NEC Communication Systems, Ltd., JAPAN
Copyright (C) 2013-2016 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
Copyright (C) 2014-2016 by SCSK Corporation, JAPAN
Copyright (C) 2013-2016 by Sunny Giken Inc., JAPAN
Copyright (C) 2015-2016 by SUZUKI MOTOR CORPORATION
Copyright (C) 2013-2016 by TOSHIBA CORPORATION, JAPAN
Copyright (C) 2013-2016 by Witz Corporation

上記著作権者は，以下の (1)～(3)の条件を満たす場合に限り，本ドキュメ
ント（本ドキュメントを改変したものを含む．以下同じ）を使用・複製・改
変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
(1) 本ドキュメントを利用する場合には，上記の著作権表示，この利用条件
    および下記の無保証規定が，そのままの形でドキュメント中に含まれて
    いること．
(2) 本ドキュメントを改変する場合には，ドキュメントを改変した旨の記述
    を，改変後のドキュメント中に含めること．ただし，改変後のドキュメ
    ントが，TOPPERSプロジェクト指定の開発成果物である場合には，この限
    りではない．
(3) 本ドキュメントの利用により直接的または間接的に生じるいかなる損害
    からも，上記著作権者およびTOPPERSプロジェクトを免責すること．また，
    本ドキュメントのユーザまたはエンドユーザからのいかなる理由に基づ
    く請求からも，上記著作権者およびTOPPERSプロジェクトを免責すること．

本ドキュメントは，AUTOSAR（AUTomotive Open System ARchitecture）仕様
に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するものではな
い．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利用する
者に対して，AUTOSARパートナーになることを求めている．

本ドキュメントは，無保証で提供されているものである．上記著作権者およ
びTOPPERSプロジェクトは，本ドキュメントに関して，特定の使用目的に対す
る適合性も含めて，いかなる保証も行わない．また，本ドキュメントの利用
により直接的または間接的に生じたいかなる損害に関しても，その責任を負
わない．

$Id: readme.txt 3128 2016-03-15 05:16:52Z fsi-kaitori $
----------------------------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(1) フォルダ構成
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

coverage
┣ check_spec_coverage.rb：仕様カバレッジチェックスクリプト
┣ get_spec_id.rb        ：AUTOSAR仕様書から仕様タグを抜き出すスクリプト
┣ get_impl_id.rb        ：get_spec_id.rbで生成したファイル
┣ com_spec.txt          ：COM外部仕様書テキスト版(同梱していない)
┣ com_spec_id.txt       ：get_spec_id.rbで生成したファイル(COM仕様一覧)
┣ com_impl_id.txt       ：get_impl_id.rbで生成したファイル(実装仕様一覧)
┗ readme.txt            ：本ドキュメント

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(2) 使い方
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

―――――――――――――――――――――――――――――――――――
(2.1) COM外部仕様書テキスト版の用意
―――――――――――――――――――――――――――――――――――

TOPPERSのWebサイト(https://www.toppers.jp/)からpdfで配布されている，
COMの外部仕様書をダウンロードし，Adobe Reader等の変換機能を使用して，
テキストファイルを作成する．
ファイル名はcom_spec.txtとして，(1)フォルダ構成 に従って配置する．

―――――――――――――――――――――――――――――――――――
(2.2) COM仕様一覧の作成
―――――――――――――――――――――――――――――――――――

$ cd coverage
$ ruby get_spec_id.rb

上記コマンドによりcom_spec_id.txtが生成される．

―――――――――――――――――――――――――――――――――――
(2.3) A-COM実装仕様一覧の作成
―――――――――――――――――――――――――――――――――――

$ cd coverage
$ ruby get_impl_id.rb

上記コマンドによりcom_impl_id.txtが生成される．

―――――――――――――――――――――――――――――――――――
(2.4) A-COMに実装された仕様カバレッジを取得する
―――――――――――――――――――――――――――――――――――

$ cd coverage
$ ruby check_spec_coverage.rb

上記コマンドにより，以下のようなカバレッジ確認結果が出力される．

$ ruby check_spec_coverage.rb
==============================
Com spec tags   : 479
Implemented tags: 479
Spec Coverage   : 100.0 %
------------------------------
Not implementation tags: 0
==============================


以上．
