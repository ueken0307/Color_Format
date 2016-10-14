Color_Format
====

##概要
カラーパレットとスライダーで指定した色を書式に従って文字列として出力するツールです
![](https://github.com/ueken0307/Color_Format/blob/master/etc/how_to_use.gif)

##似たようなwebサービスがいっぱいあるのになんで作ったの？
確かにRGBをスライダーなどで決定して色をプレビューしてくれるサービスはいっぱいあります。  
しかし、それをプログラムなどに組み込むときには、それをもとに手入力したり、RGBを1つ1つコピーして貼り付けたりする必要が出てきます。  
これは時間の無駄と思いこのアプリケーションを作成しました。~~作者が楽したかっただけです~~  

##使い方
appフォルダ内のColor_Format.exeを実行（単体で動きます）  
↓  
カラーパレットやスライダーを用いたり、数値を直接入力したりして色を決める  
↓  
RGB,BGR,HTMLの中から自分の用途にあったものを選び、書式を指定する  
↓  
"クリップボードにコピー"ボタンを押すとコピーされる  

**"自動でクリップボードにコピー"を選択すると、**  
**毎回毎回"クリップボードにコピー"を押す必要がなくなります**  

##書式指定
書式の中に@を3つ書くと、それぞれの場所に指定されたRGBの値を入れます。  
また、出力の順番や、出力の形式を、RGB,BGR,HTMLの中から選ぶことができます。  
※HTMLを選んだ場合は書式を指定する必要はありません  

**例**  
色→R=10 G=20 B=30 書式→ Color(@,@,@)の場合  
RGB → Color(10,20,30)  
BGR → Color(30,20,10)  
HTML → #0a141e  

##開発環境
言語 C++  
ライブラリ Siv3D  
IDE VisualStudio2015  

##動作環境
確認済　Windows 8.1 /Windows 10  

##その他
BGRはほぼopencv用です(?)  
  
[アイコン用にお借りした画像](http://www.ac-illust.com/main/detail.php?id=555473&word=%25E8%2589%25B2%25E7%259B%25B8%25E7%2592%25B0RGB)  
  
製作者 [@zuho_cpp](https://twitter.com/zuho_cpp)  

~~かっこいいアプリ名考えようと思ったんですけど、英語の知識がnainaiすぎてクソみたいな名前になったのは触れちゃだめです。~~  