
	TOPPRES/A-COM サンプルプログラム実行手順

本ドキュメントは，TOPPRES/A-COMの動作確認のためのサンプルプログラムを
TOPPERS/ATK2で実行する手順を示す．

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
a-comstack/com/sample/Makefile -> SRCDIR="../../../atk2-sc1"

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(4) COMコンフィギュレーション
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

AUTOSAR仕様に従って，COMのコンフィギュレーション情報をcom.arxmlとして作
成する．A-COM付属のXML生成ツールを用いると，YAMLフォーマットで記述した
コンフィギュレーション情報をarxmlフォーマットへ変換することができる．

■実行ファイル
  a-comstack/utils/abrex/abrex.rb

■マニュアル
  a-comstack/utils/abrex/readme.txt

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(5) COMジェネレーション
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

以下のコマンドにより，com.arxmlからコンフィギュレーションに従ったフ
ァイル群を生成する．

$ cd a-comstack/com/sample
$ make com

※com.arxmlとは別のarxmlからジェネレーションを実行したい場合，
  MakefileのCOM_CFGNAMEを変更する
※ジェネレーションしたファイルを削除する場合は以下を実行する
  $ make comclean

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

$ cd a-comstack/com/sample
$ make depend
$ make
$ make run

―――――――――――――――――――――――――――――――――――
(6.3) サンプルプログラム概要
―――――――――――――――――――――――――――――――――――

本サンプルプログラムは，A-COMの基本的な動作を確認するためのものであり，
以下の機能を実行する．

・初期化                       : Com_Init
・COM状態取得                  : Com_GetStatus
・コンフィギュレーションID取得 : Com_GetConfigurationId
・バージョン情報取得           : Com_GetVersionInfo
・IPDUグループベクタクリア     : Com_ClearIpduGroupVector
・IPDUグループベクタ設定       : Com_SetIpduGroup
・IPDUグループ起動             : Com_IpduGroupControl
・シグナル送信                 : Com_SendSignal
・モード切替                   : Com_SwitchIpduTxMode
・シグナルグループ送信         : Com_SendSignalGroup
・トリガ送信                   : Com_TriggerIPDUSend
・無効値シグナル送信           : Com_InvalidateSignal
・無効値シグナルグループ送信   : Com_InvalidateSignalGroup
・周期送信                     : Com_MainFunctionTx
・送信完了通知                 : Com_TxConfirmation
・IPDU受信                     : Com_RxIndication
・周期受信                     : Com_MainFunctionRx
・シグナル受信                 : Com_ReceiveSignal
・シグナルグループ受信         : Com_ReceiveSignalGroup
・未初期化                     : Com_DeInit

以上．
