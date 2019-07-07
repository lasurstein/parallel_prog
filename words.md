計算言語    個々の活動を記述するプログラミング言語（e.g., C, Fortran）

協調言語    統一されたプログラムを組み立てる言語（e.g., Linda, 同期通信ライブラリ）

バッチ処理  入出力処理とCPU計算処理を並列で行う → 高価なCPUの有効活用方法

RPC       Remote Procedure Call. 遠隔手続き呼出．

NFS       Network File System. 機室でWindows/Ubuntuを起動できるのはNFSのおかげ．

NIS       Network Information System. NFSのためのUID/Pass共通の仕組み

ORM       Object Request Broker. 複数の言語をつなぐためのオブジェクト指向RPC．

CP/M      Control Program for Microcomputers.

MS-DOS    CP/MにUnixのような機能を導入したもの．階層化ディレクトリ構造，子プロセス生成．

SISD      Single Instruction, Single Data  
SIMD      Single Instruction, Multiple Data  
MISD      Multiple Instruction, Single Data  
MIMD      Multiple Instruction, Multiple Data

MIMDの分類
+ 共有メモリがある（with shared memory）
+ 共有メモリがない（without shared memory）

UMA       Uniform Memory Access  
SMP       Symmetric Multiprocessor. Shared memory multiprocessor. 共有メモリ型マルチプロセッサ．メモリへのアクセス時間がどの場所も対称的で均質．  
NUMA      Non-uniform Memory Access  
NORMA     No-Remote Memory Access  

Machintoshにおける分類
+ 共有メモリがある
  + アクセスが均一（UMA, SMP）
  + アクセスが不均一（NUMA）
+ 共有メモリがない（NORMA）

MMU       Memory Management Unit.

DMA       Direct Memory Access.