
	TOPPRES/A-CANTP サンプルプログラム実行手順

本ドキュメントは，TOPPRES/A-CANTPの動作確認のためのサンプルプログラムを
TOPPERS/ATK2で実行する手順を示す．

----------------------------------------------------------------------
TOPPRES/A-CANTP
    Automotive CANTP

Copyright (C) 2016-2017 by Center for Embedded Computing Systems
                           Graduate School of Information Science, Nagoya Univ., JAPAN
Copyright (C) 2016-2017 by FUJI SOFT INCORPORATED, JAPAN
Copyright (C) 2016-2017 by NEC Communication Systems, Ltd., JAPAN
Copyright (C) 2016-2017 by SCSK Corporation, JAPAN
Copyright (C) 2016-2017 by SUZUKI MOTOR CORPORATION
Copyright (C) 2016-2017 by TOSHIBA CORPORATION, JAPAN
Copyright (C) 2016-2017 by Witz Corporation

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

$Id: readme.txt 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
----------------------------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(1) TOPPERS/ATK2動作環境の用意
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

TOPPERS/ATK2を入手し，付属のサンプルプログラムが動作する環境を構築する．

※現時点での動作確認環境は以下
・TOPPERS/ATK2-SC1
  ・at91skyeye_gcc
  ・nios2_dev_gcc
※以下，TOPPERS/ATK2-SC1を使用した場合の手順を示す

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(2) COMスタックの用意
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

atk2-sc1フォルダを相対パスで指定可能な位置へ，a-comstackフォルダを配置
する．

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(3) パスの設定
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Makefileを開き，atk2-sc1フォルダへの相対パスを，環境変数SRCDIRへ設定す
る．デフォルトでは，以下のフォルダ構成を想定した状態となっている．

atk2-sc1  /cfg/cfg/cfg.exe
            :
a-comstack/cantp/sample/Makefile -> SRCDIR="../../../atk2-sc1"

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(4) CANTPコンフィギュレーション
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

AUTOSAR仕様に従って，CANTPのコンフィギュレーション情報をcantp.arxmlとし
て作成する．A-CANTP付属のXML生成ツールを用いると，YAMLフォーマットで記
述したコンフィギュレーション情報をarxmlフォーマットへ変換することができ
る．

■実行ファイル
  a-comstack/utils/abrex/abrex.rb

■マニュアル
  a-comstack/utils/abrex/readme.txt

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(5) CANTPジェネレーション
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

以下のコマンドにより，cantp.arxmlからコンフィギュレーションに従ったファ
イル群を生成する．

$ cd a-comstack/cantp/sample
$ make cantp

※cantp.arxmlとは別のarxmlからジェネレーションを実行したい場合，
  MakefileのCANTP_CFGNAMEを変更する
※ジェネレーションしたファイルを削除する場合は以下を実行する
  $ make cantpclean

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(6) サンプルプログラムビルド＆実行
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

―――――――――――――――――――――――――――――――――――
(6.1) ターゲットの指定
―――――――――――――――――――――――――――――――――――

MakefileのTARGETを変更し，実行するターゲットを指定する．

―――――――――――――――――――――――――――――――――――
(6.2) ビルド＆実行
―――――――――――――――――――――――――――――――――――

$ cd a-comstack/cantp/sample
$ make depend
$ make
$ make run

―――――――――――――――――――――――――――――――――――
(6.3) サンプルプログラム概要
―――――――――――――――――――――――――――――――――――

本サンプルプログラムは，A-CANTPの基本的な動作を確認するためのものであ
り，以下の処理を順に実行する．
※本サンプルプログラムはat91skyeye_gccの環境で実行すること

・初期化                       : CanTp_Init
・バージョン情報取得           : CanTp_GetVersionInfo

--CAN通信--
シングルフレーム送信
・送信要求                     : CanTp_Transmit
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction

マルチフレーム送信
・送信要求                     : CanTp_Transmit
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction

シングルフレーム受信
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction

マルチフレーム受信確認
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction

--CANFD通信--
シングルフレーム送信
・送信要求                     : CanTp_Transmit
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction

マルチフレーム送信
・送信要求                     : CanTp_Transmit
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction

シングルフレーム受信
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction

マルチフレーム受信確認
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction
・送信完了通知                 : CanTp_TxConfirmation
・周期処理                     : CanTp_MainFunction
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction
・受信完了通知                 : CanTp_RxIndication
・周期処理                     : CanTp_MainFunction

・シャットダウン               : CanTp_Shutdown

以上．
