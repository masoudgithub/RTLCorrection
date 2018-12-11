; ModuleID = 'fir.1.bc'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-unknown-linux-gnu"

@main.coefficients = private unnamed_addr constant [16 x i32] [i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10], align 4
@.str = private unnamed_addr constant [12 x i8] c"Result: %d\0A\00", align 1
@.str1 = private unnamed_addr constant [14 x i8] c"RESULT: PASS\0A\00", align 1
@.str2 = private unnamed_addr constant [14 x i8] c"RESULT: FAIL\0A\00", align 1

; Function Attrs: nounwind
define i32 @main() #0 {
  %previous = alloca [16 x i32], align 4
  br label %1

; <label>:1                                       ; preds = %2, %0
  %indvar4 = phi i32 [ %indvar.next5, %2 ], [ 0, %0 ]
  %s.i.0 = getelementptr [16 x i32]* %previous, i32 0, i32 %indvar4
  %exitcond = icmp eq i32 %indvar4, 16
  br i1 %exitcond, label %legup_memset_4.exit, label %2

; <label>:2                                       ; preds = %1
  store i32 0, i32* %s.i.0, align 4
  %indvar.next5 = add i32 %indvar4, 1
  br label %1

legup_memset_4.exit:                              ; preds = %1
  %3 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 0
  %4 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 14
  %5 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 15
  %6 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 13
  %7 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 12
  %8 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 11
  %9 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 10
  %10 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 9
  %11 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 8
  %12 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 7
  %13 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 6
  %14 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 5
  %15 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 4
  %16 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 3
  %17 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 2
  %18 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 1
  br label %19

; <label>:19                                      ; preds = %FIRFilterStreaming.exit, %legup_memset_4.exit
  %indvar = phi i32 [ %indvar.next, %FIRFilterStreaming.exit ], [ 0, %legup_memset_4.exit ]
  %20 = phi i32 [ 0, %legup_memset_4.exit ], [ %indvar, %FIRFilterStreaming.exit ]
  %21 = phi i32 [ 0, %legup_memset_4.exit ], [ %20, %FIRFilterStreaming.exit ]
  %22 = phi i32 [ 0, %legup_memset_4.exit ], [ %21, %FIRFilterStreaming.exit ]
  %23 = phi i32 [ 0, %legup_memset_4.exit ], [ %22, %FIRFilterStreaming.exit ]
  %24 = phi i32 [ 0, %legup_memset_4.exit ], [ %23, %FIRFilterStreaming.exit ]
  %25 = phi i32 [ 0, %legup_memset_4.exit ], [ %24, %FIRFilterStreaming.exit ]
  %26 = phi i32 [ 0, %legup_memset_4.exit ], [ %25, %FIRFilterStreaming.exit ]
  %27 = phi i32 [ 0, %legup_memset_4.exit ], [ %26, %FIRFilterStreaming.exit ]
  %28 = phi i32 [ 0, %legup_memset_4.exit ], [ %27, %FIRFilterStreaming.exit ]
  %29 = phi i32 [ 0, %legup_memset_4.exit ], [ %28, %FIRFilterStreaming.exit ]
  %30 = phi i32 [ 0, %legup_memset_4.exit ], [ %29, %FIRFilterStreaming.exit ]
  %31 = phi i32 [ 0, %legup_memset_4.exit ], [ %30, %FIRFilterStreaming.exit ]
  %32 = phi i32 [ 0, %legup_memset_4.exit ], [ %31, %FIRFilterStreaming.exit ]
  %33 = phi i32 [ 0, %legup_memset_4.exit ], [ %32, %FIRFilterStreaming.exit ]
  %total.02 = phi i32 [ 0, %legup_memset_4.exit ], [ %42, %FIRFilterStreaming.exit ]
  %i.01 = add i32 %indvar, 1
  store i32 %33, i32* %5, align 4, !tbaa !1
  store i32 %32, i32* %4, align 4, !tbaa !1
  store i32 %31, i32* %6, align 4, !tbaa !1
  store i32 %30, i32* %7, align 4, !tbaa !1
  store i32 %29, i32* %8, align 4, !tbaa !1
  store i32 %28, i32* %9, align 4, !tbaa !1
  store i32 %27, i32* %10, align 4, !tbaa !1
  store i32 %26, i32* %11, align 4, !tbaa !1
  store i32 %25, i32* %12, align 4, !tbaa !1
  store i32 %24, i32* %13, align 4, !tbaa !1
  store i32 %23, i32* %14, align 4, !tbaa !1
  store i32 %22, i32* %15, align 4, !tbaa !1
  store i32 %21, i32* %16, align 4, !tbaa !1
  store i32 %20, i32* %17, align 4, !tbaa !1
  store i32 %indvar, i32* %18, align 4, !tbaa !1
  store i32 %i.01, i32* %3, align 4, !tbaa !1
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %FIRFilterStreaming.exit, label %.preheader.i.preheader

.preheader.i.preheader:                           ; preds = %19
  br label %.preheader.i

.preheader.i:                                     ; preds = %.preheader.i, %.preheader.i.preheader
  %j.02.i = phi i32 [ %41, %.preheader.i ], [ 0, %.preheader.i.preheader ]
  %temp.01.i = phi i32 [ %40, %.preheader.i ], [ 0, %.preheader.i.preheader ]
  %scevgep = getelementptr [16 x i32]* @main.coefficients, i32 0, i32 %j.02.i
  %35 = mul i32 %j.02.i, -1
  %36 = add i32 %35, 15
  %scevgep2 = getelementptr [16 x i32]* %previous, i32 0, i32 %36
  %37 = load i32* %scevgep2, align 4, !tbaa !1
  %38 = load i32* %scevgep, align 4, !tbaa !1
  %39 = mul nsw i32 %38, %37
  %40 = add nsw i32 %39, %temp.01.i
  %41 = add nsw i32 %j.02.i, 1
  %exitcond1 = icmp eq i32 %41, 16
  br i1 %exitcond1, label %FIRFilterStreaming.exit.loopexit, label %.preheader.i

FIRFilterStreaming.exit.loopexit:                 ; preds = %.preheader.i
  %.lcssa = phi i32 [ %40, %.preheader.i ]
  br label %FIRFilterStreaming.exit

FIRFilterStreaming.exit:                          ; preds = %FIRFilterStreaming.exit.loopexit, %19
  %.0.i = phi i32 [ 0, %19 ], [ %.lcssa, %FIRFilterStreaming.exit.loopexit ]
  %42 = add i32 %.0.i, %total.02
  %indvar.next = add i32 %indvar, 1
  %exitcond3 = icmp eq i32 %indvar.next, 32
  br i1 %exitcond3, label %43, label %19

; <label>:43                                      ; preds = %FIRFilterStreaming.exit
  %.lcssa8 = phi i32 [ %42, %FIRFilterStreaming.exit ]
  %44 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([12 x i8]* @.str, i32 0, i32 0), i32 %.lcssa8) #1
  %45 = icmp eq i32 %.lcssa8, 44880
  br i1 %45, label %46, label %48

; <label>:46                                      ; preds = %43
  %47 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str1, i32 0, i32 0)) #1
  br label %50

; <label>:48                                      ; preds = %43
  %49 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str2, i32 0, i32 0)) #1
  br label %50

; <label>:50                                      ; preds = %48, %46
  ret i32 %.lcssa8
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) #0

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nobuiltin nounwind }

!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}

!0 = metadata !{metadata !"clang version 3.5.0 (tags/RELEASE_350/final)"}
!1 = metadata !{metadata !2, metadata !2, i64 0}
!2 = metadata !{metadata !"int", metadata !3, i64 0}
!3 = metadata !{metadata !"omnipotent char", metadata !4, i64 0}
!4 = metadata !{metadata !"Simple C/C++ TBAA"}
