
	TOPPRES/A-COMSTACK

本ドキュメントは，A-COMSTACKを使用する上で必要な情報を紹介する．

----------------------------------------------------------------------
TOPPRES/A-COMSTACK
    Automotive COMSTACK

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

$Id: readme.txt 2995 2016-03-02 02:05:09Z fsi-kaitori $
----------------------------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(1) 概要
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

TOPPERS/A-COMSTACKは，AUTOSARで定義されている通信スタックのうち，以下の
4つのモジュールを含んでいる．

・Com（Communication）  : A-COM
・PduR（PDU Router）    : A-PDUR
・CanIf（CAN Interface）: A-CANIF
・Can（CAN Driver）     : A-CAN

Canはハードウェアに依存したモジュールであり，TOPPERS/A-COMSTACKのA-CAN
は依存部として以下を用意している．
・nios2_dev_gcc依存部
・hsbv850e2fg4_cx依存部

それぞれのモジュールに関する詳細は，外部仕様書または各モジュールフォル
ダのdocフォルダにあるドキュメントを参照すること．

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(2) TOPPERS/ATK2上での使い方
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
―――――――――――――――――――――――――――――――――――
(2.1) 動作環境
―――――――――――――――――――――――――――――――――――

TOPPERS/ATK2を入手し，付属のサンプルプログラムが動作する環境を構築する．
また，ATK2付属のXML生成ツール(ABREX)も使用するため，Rubyも必要となる．

※現時点での動作確認環境は以下
・TOPPERS/ATK2-SC1 (nios2_dev_gcc依存部)

―――――――――――――――――――――――――――――――――――
(2.2) フォルダ構成
―――――――――――――――――――――――――――――――――――

TOPPERS/ATK2，TOPPERS/A-COMSTACKを入手し，以下のように同一フォルダ内に
配置する．

┣ a-comstack         ：A-COMSTACK
┃ ┣ com             ：A-COM
┃ ┃  ┣ coverage    ：A-COM用仕様カバレッジチェックツール
┃ ┃  ┣ performance ：A-COM用性能評価プログラム
┃ ┃  ┗ sample      ：A-CANIF用サンプルアプリケーション
┃ ┃
┃ ┣ pdur            ：A-PDUR
┃ ┃  ┣ doc         ：A-PDUR用ドキュメント
┃ ┃  ┗ sample      ：A-PDUR用サンプルコンフィギュレーション
┃ ┃
┃ ┣ canif           ：A-CANIF
┃ ┃  ┣ coverage    ：A-CANIF用仕様カバレッジチェックツール
┃ ┃  ┣ doc         ：A-CANIF用ドキュメント
┃ ┃  ┗ sample      ：A-CANIF用サンプルアプリケーション
┃ ┃
┃ ┣ can             ：A-CAN
┃ ┃  ┣ arch        ：A-CAN用アーキテクチャ
┃ ┃  ┣ coverage    ：A-CAN用仕様カバレッジチェックツール
┃ ┃  ┣ doc         ：A-CAN用ドキュメント
┃ ┃  ┣ stub        ：A-CAN用スタブ
┃ ┃  ┗ target      ：A-CAN用ターゲット依存部
┃ ┃
┃ ┣ general         ：全モジュールで使用するソースコード
┃ ┃
┃ ┣ stub            ：A-COMSTACK以外のAUTOSARモジュールスタブ
┃ ┃
┃ ┣ doc             ：A-COMSTACK用ドキュメント
┃ ┃
┃ ┗ utils           ：ユーティリティプログラム
┃     ┗ abrex       ：ARXML生成ツール
┃ 
┗ atk2-sc1           ：ATK2-SC1

―――――――――――――――――――――――――――――――――――
(2.3) サンプルアプリケーションの実行
―――――――――――――――――――――――――――――――――――

各モジュールフォルダのsample内にあるreadme.txtに従って，サンプルアプリ
ケーションを実行する．



以上．
