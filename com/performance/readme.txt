
	TOPPRES/A-COM 性能評価プログラム実行手順

本ドキュメントは，TOPPRES/A-COMの性能評価プログラムを実行する手順を示す．

----------------------------------------------------------------------
TOPPRES/A-COM
    Automotive COM

Copyright (C) 2013-2014 by Center for Embedded Computing Systems
            Graduate School of Information Science, Nagoya Univ., JAPAN
Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
Copyright (C) 2013-2014 by TOSHIBA CORPORATION, JAPAN
Copyright (C) 2013-2014 by Witz Corporation, JAPAN

上記著作権者は，以下の (1)〜(3)の条件を満たす場合に限り，本ドキュメ
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

$Id: readme.txt 425 2014-09-17 00:46:01Z fsi-dankei $
----------------------------------------------------------------------

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(1) TOPPERS/ATK2動作環境の用意
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

TOPPERS/ATK2を入手し，付属のサンプルプログラムが動作する環境を構築する．

※現時点での動作確認環境は以下
・TOPPERS/ATK2-SC1
  ・fl850pj4_gcc
  ・nios2_dev_gcc
※本性能評価プログラムは，TOPPERS/ATK2に付属の実行時間分布集計モジュー
  ル(histogram.c)を使用する
※以下，TOPPERS/ATK2-SC1を使用した場合の手順を示す

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(2) COMスタックと，性能評価プログラムの用意
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

atk2-sc1フォルダを相対パスで指定可能な位置へ，a-comstackフォルダを配置
する．

※コンフィギュレーションはAUTOSAR R4.0.2のコンフォーマンステストのset1
  をベースにR4.0.3へ修正したものを使用する
※性能測定対象は，os.cを参照する

＜測定例＞
シグナルID:0に対して，Com_SendSignalを10000回実行し，実行時間の分布を表
示する．毎回同じ条件(IPDU，フィルタの状態)とするため，実行前にIPDUの初
期化を行う．

syslog(LOG_NOTICE, "== Com_SendSignal(0) ==");
init_hist(1, MAX_TIME, histarea);
for (i = 0; i < LOOP_COUNT; i++) {
	Com_IpduGroupControl(vector_on, TRUE);
	begin_measure(1);
	ercd = Com_SendSignal(0, &signal_sint8);
	end_measure(1);
	Com_IpduGroupControl(vector_off, TRUE);
}
print_hist(1);

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(3) パスの設定
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Makefileを開き，atk2-sc1フォルダへの相対パスを，環境変数SRCDIRへ設定す
る．デフォルトでは，以下のフォルダ構成を想定した状態となっている．

atk2-sc1  /cfg/cfg/cfg.exe
            :
a-comstack/com/sample/Makefile -> SRCDIR="../../../atk2-sc1"

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
(4) 性能評価プログラム実行
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

―――――――――――――――――――――――――――――――――――
(4.1) ターゲットの指定
―――――――――――――――――――――――――――――――――――

MakefileのTARGETを変更し，実行するターゲットを指定する．

―――――――――――――――――――――――――――――――――――
(4.2) ビルド＆実行
―――――――――――――――――――――――――――――――――――

$ cd a-comstack/com/performance
$ make depend
$ make
$ make run



以上．
