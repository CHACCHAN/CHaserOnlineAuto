# CHaserOnlineAuto - v2.1
**制作 三郷工業技術高等学校 電子計算機部**
  
 ## 更新内容
 ┣➜ マップシステム用の変数が公開されました。 
 ┣➜ [新機能] アクセス設定ができるようになりました。 
 ┗➜ [追加] MapDataを追加しました。 
  
 ## 概要
 ┣➜ CHaserOnlineより快適に実行出来るように開発されたものです。 
 ┗➜ このプログラムはC言語で作られています。 
  
 ## 推奨ハードウェア条件 
 ┣➜ CPU   : 2010年以降のIntel製CPU、AMD製CPU
 ┗➜ メモリ : DDR3 1333MHz 512MB 以上 
  
 ## 対応プラットフォーム 
 ┣➜ Linuxのみ 
 ┗➜ (Ubuntu 20.04、CentOS7、WSL2で動作確認済み) 
  
 ## 必要ソフトウェア 
 ┗➜ gcc version 11.3.0以上 
  
 ## ディレクトリ構成 
```
 CHaserOnlineAuto-v2.1 
 ┣ Config 
 |    ┣ addressconfig.txt ･･･ アクセス設定ファイル 
 |    ┗ userconfig.txt ･･･ ユーザー設定ファイル 
 ┣ src  
 |   ┣ Cash 
 |   |   ┗ UserCheckFlag.txt ･･･ 伝達一時キャッシュファイル 
 |   ┣ Header 
 |   |   ┣ CHaserOnline2023.h ･･･ CHaserOnlineヘッダーファイル 
 |   |   ┣ CHaserTools.h ･･･ CHaserOnline便利関数ヘッダー 
 |   |   ┗ MapSystem.h ･･･ CHaserOnlineマップ関係ヘッダー 
 |   | 
 |   ┣ Action.c ･･･ Actionのコマンド定義ファイル 
 |   ┣ Base.c ･･･ CHaserOnline本体 
 |   ┣ Command.c ･･･ CHaserOnline命令ファイル 
 |   ┗ GetReady.c ･･･GetReadyコマンド定義ファイル 
 | 
 ┣ CHaserOnline.c ･･･ CHaserOnline実行補助ファイル 
 ┣ ErrorHelp.txt ･･･ エラーコード一覧ファイル 
 ┣ README.md ･･･　説明書 
 ┗ start.sh ･･･ 実行スクリプト 
  ```
 
  
## 実践 
 　　1. CHaserOnlineのアカウント登録をしよう！ 
 　　　まず始めに、自身のCHaserOnlineアカウントの登録を行います。 
 　　　/Config/userconfig.txt から""で囲まれたところにID、パスワードを入力して保存してください。 
 　　　初期状態では、coolとhotアカウントが設定されています。 
  
     2. アクセス情報を設定しよう！(重要) 
       /config/addressconfig.txt から2行目の""で囲まれたところにCHaserOnlineサーバーURLを入力、 
       4行目の""で囲まれたところにプロキシアドレスを入力してください。 
       空欄だと接続自体が不可になりますので必ず入れてください。 
       初期状態では、CHaserOnlineサクラサーバー、校内プロキシを設定しています。 
  
 　　3. CHaserOnlineの作戦を考えよう！ 
 　　　次に、CHaserOnlineの作戦を考えます。 
 　　　/src/Command.c から"//GetReadyの作戦はここから"と"//Actionの作戦はここから"で囲われたところにそれぞれGetReadyとActionの作戦を記入します。 
 　　　初期状態では参考として、ジオーメタルを回収するプログラムが書かれています。 
  
 　　4. 効率的にコーディングをしよう！ 
 　　　作戦のプログラムを作成するときに処理に困ったりすることがあるので、CHaserOnlineAutoでは短縮したり、自動化できる簡単作戦ツールを用意しています！ 
 　　　簡単作戦ツールとは...パターン化された処理や長くなる処理、自動化などCHaserOnlineをプレイしていく上でよく使う処理を一つの関数にしたものです。 
 　　　代表的なものだと、SelectID()などです。これらのツールを多用し、効率的なCHaserOnlineにしましょう！ 
 　　　関数リストや説明は項目「簡単作戦ツール」をご覧ください。 
 　　　また、MapSystemというものがありマップ上の情報を常に記録してくれているものがあります。 
 　　　マップ情報を参照して作戦に役立てるというやり方もありますので、詳しい使い方は項目「MapSystem の使い方」をご覧ください。 
  
## 起動 
 　　※初回起動の場合 
 　　最初だけやらなくてはならない設定があります。 
 　　設定を無視すると、以下のようなエラーが表示されます。 
 　　[ -bash: ./start.sh: Permission denied ](実行権限がありません) 
  
 　　パスCHaserOnlineAuto-v*/ で、以下のコマンドを実行してください。 
 　　$ chmod 775 start.sh 
 　　($ は抜きで入力してください) 
 　　これで、次回から[ ./start.sh ]で起動できます！ 
  
## start.sh の使い方
 　　このスクリプトファイルは、以下のコマンドを自動的に実行します。 
 　　1. gcc -o CHaserOnline CHaserOnline.c ・・・ gccコンパイラを用いてCHaserOnline.cをCHaserOnlineという実行可能ファイルにコンパイルする。 
 　　2. clear ・・・ ターミナルをクリアする。 
 　　3. ./CHaserOnline ・・・ 実行可能ファイルのCHaserOnlineをBASHで実行する。 
  
## CHaserOnline.c の使い方
 　　このソースファイルは、CHaserOnlineAutoの本体になります。 
 　　実行すると、次のような指示がありますので、それについて解説します。 
  
 　　✔ 最初にアカウントの選択を行い、それぞれ実行方法を選択します。 
 　　　 ([通常]は一度だけの実行、[連続]は指定したルーム分実行) 
  
 　　✔ [通常]を選択すると、ルーム番号とプロキシアドレスの有無を聞かれます。 
 　　　 校内ではプロキシを利用するため"Y"を選択、自宅では不要なので"N"を選択してください。 
 　　　 選択を終えると、Action.cとBase.cとCommand.cとGetReady.cのコンパイルが自動的に行われCHaserOnlineが実行されます。 
  
 　　✔ [連続]を選択すると、最初のルーム番号から終わりのルーム番号とプロキシアドレスの有無を聞かれます。 
 　　　 校内ではプロキシを利用するため"Y"を選択、自宅では不要なので"N"を選択してください。 
 　　　 もし、途中で参加できないルームがあれば自動的にスキップされます。 
 　　　 選択を終えると、Action.cとBase.cとCommand.cとGetReady.cのコンパイルが自動的に行われ指定したルーム分CHaserOnlineが実行されます。 
  
 
## MapSystem の使い方 
 　　MapSystemとは...取得した情報を多様な角度から常に記録していたり、判断してくれたりしてくれる頼れる味方です。 
 　　MapSystemには、次のような変数が用意されています。 
 　　 1. MapData[19][19] ･･･ マップ情報19x19分を格納 
 　　 2. MoveX ･･･ 一度のコマンドで進んだX座標の距離 
 　　 3. MoveY ･･･ 一度のコマンドで進んだY座標の距離 
 　　 4. MapX  ･･･ 合計したときのX座標の移動距離 
 　　 5. MapY  ･･･ 合計したときのY座標の移動距離 
  
 　　MapData[19][19]は、MapData[X座標][Y座標]と定義しており、基本的にX:9,Y:9を真ん中として記録しています。 
 　　この配列に格納される値は以下のパターンのみになります。 
 　　 1. [-2] ･･･ まだ記録できない不明地の値 
 　　 2. [1]  ･･･ 場外の値 
 　　 3. [?]  ･･･ 0や70などのただのアイテム番号(CHaserOnline2023に基づく) 
  
  
## ヘルパー関数
 SelectID関数
 ライブラリ : CHaserTools.h 
 書式       : int SelectID(int data, int start, int end); 
  
 →説明 
 　以下の例のように、連続した値を比較するプログラムを作ると長くなってしまいます。 
 　それを、解決するために作られた関数です。 
 　int data はSelectID関数に参照してもらう値を入れる引数になります。 
 　int startは参照値の開始値、int endは参照値の終了値になり、 
 　int start = 70,int end = 79で、70～79という意味になります。 
  
 ✔ 使用例 
```
 // 従来の方法だと 
 if(returnNumber[0] == 70 || returnNumber[0] == 71 || returnNumber[0] == 72 || returnNumber[0] == 73 || returnNumber[0] == 74 ・・・etc・・・== 79) 
 // とても長くなる 
```
```
 // SelectIDを使うと 
 if(returuNumber[0] == SelectID(returnNumber[0],70,79)) 
 // 短くできる 
```
  
 SelectID_some関数
 ライブラリ : CHaserTools.h 
 書式       : int SelectID_some(int data,int select, ... ); 
  
 →説明 
 　以下の例のように、連続した不規則な値を比較するプログラムを作ると長くなってしまいます。 
 　それを解決するために作られた関数です。 
 　これは、SelectID関数の付属するもので連続した値では無く不規則な値を比較するのに用いられます。 
 　int data はSelectID_some関数に参照してもらう値を入れる引数になります。 
 　int selectは参照値の個数を指定するための引数になります。 
 　...部分は可変引数になり、selectで指定した分の値を入れることができます。 
  
 ✔ 使用例 
```
 // 従来の方法だと 
 if(returnNumber[0] == 0 || returnNumber[0] == 5 || returnNumber[0] == 61 ・・・etc・・・==63) 
 // とても長くなる 
```
```
 // SelectID_someを使うと 
 if(returnNumber[0] == SelectID_some(returnNumber[0],4,0,5,61,63)) 
 // 短くできる 
```
  
RemoveSubString関数
 ライブラリ : CHaserTools.h 
 書式       : char* RemoveSubString(const char* input, const char* substring); 
  
 →説明 
 　文字列の一部を切り取って出力できる関数になります。 
 　char* inputに元の文字列、char* substringに削除を指定する文字列を入れます。 
 　通常必要ありませんが、free(変数)でメモリ解放することを推奨します。 
  
 ✔ 使用例 
```
 char str1[] = "HelloWorld!EVERYONE!"; 
 char str2[] = "EVERYONE!"; 
 char* result; 
  
 result = RemoveSubString(str1,str2); 
  
 printf("%s\n",result); 
 free(result); 
 ```

 出力結果
 ```HelloWorld!```