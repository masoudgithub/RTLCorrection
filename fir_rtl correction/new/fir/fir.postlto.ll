; ModuleID = 'fir.postlto.bc'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-unknown-linux-gnu"

@main.coefficients = private unnamed_addr constant [16 x i32] [i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10, i32 10], align 4
@.str = private unnamed_addr constant [12 x i8] c"Result: %d\0A\00", align 1
@.str1 = private unnamed_addr constant [14 x i8] c"RESULT: PASS\0A\00", align 1
@.str2 = private unnamed_addr constant [14 x i8] c"RESULT: FAIL\0A\00", align 1

; Function Attrs: nounwind
define i32 @main() #0 {
  %previous = alloca [16 x i32], align 4
  %1 = bitcast [16 x i32]* %previous to i8*
  %2 = bitcast i8* %1 to i32*
  br label %3

; <label>:3                                       ; preds = %7, %0
  %s.i.0 = phi i32* [ %2, %0 ], [ %8, %7 ]
  %4 = phi i32 [ %5, %7 ], [ 16, %0 ]
  %5 = add i32 %4, -1
  %6 = icmp eq i32 %4, 0
  br i1 %6, label %legup_memset_4.exit, label %7

; <label>:7                                       ; preds = %3
  %8 = getelementptr inbounds i32* %s.i.0, i32 1
  store i32 0, i32* %s.i.0, align 4
  br label %3

legup_memset_4.exit:                              ; preds = %3
  %9 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 0
  %10 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 14
  %11 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 15
  %12 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 13
  %13 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 12
  %14 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 11
  %15 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 10
  %16 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 9
  %17 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 8
  %18 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 7
  %19 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 6
  %20 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 5
  %21 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 4
  %22 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 3
  %23 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 2
  %24 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 1
  br label %25

; <label>:25                                      ; preds = %FIRFilterStreaming.exit, %legup_memset_4.exit
  %26 = phi i32 [ 0, %legup_memset_4.exit ], [ %i.01, %FIRFilterStreaming.exit ]
  %27 = phi i32 [ 0, %legup_memset_4.exit ], [ %26, %FIRFilterStreaming.exit ]
  %28 = phi i32 [ 0, %legup_memset_4.exit ], [ %27, %FIRFilterStreaming.exit ]
  %29 = phi i32 [ 0, %legup_memset_4.exit ], [ %28, %FIRFilterStreaming.exit ]
  %30 = phi i32 [ 0, %legup_memset_4.exit ], [ %29, %FIRFilterStreaming.exit ]
  %31 = phi i32 [ 0, %legup_memset_4.exit ], [ %30, %FIRFilterStreaming.exit ]
  %32 = phi i32 [ 0, %legup_memset_4.exit ], [ %31, %FIRFilterStreaming.exit ]
  %33 = phi i32 [ 0, %legup_memset_4.exit ], [ %32, %FIRFilterStreaming.exit ]
  %34 = phi i32 [ 0, %legup_memset_4.exit ], [ %33, %FIRFilterStreaming.exit ]
  %35 = phi i32 [ 0, %legup_memset_4.exit ], [ %34, %FIRFilterStreaming.exit ]
  %36 = phi i32 [ 0, %legup_memset_4.exit ], [ %35, %FIRFilterStreaming.exit ]
  %37 = phi i32 [ 0, %legup_memset_4.exit ], [ %36, %FIRFilterStreaming.exit ]
  %38 = phi i32 [ 0, %legup_memset_4.exit ], [ %37, %FIRFilterStreaming.exit ]
  %39 = phi i32 [ 0, %legup_memset_4.exit ], [ %38, %FIRFilterStreaming.exit ]
  %40 = phi i32 [ 0, %legup_memset_4.exit ], [ %39, %FIRFilterStreaming.exit ]
  %total.02 = phi i32 [ 0, %legup_memset_4.exit ], [ %50, %FIRFilterStreaming.exit ]
  %i.01 = phi i32 [ 1, %legup_memset_4.exit ], [ %51, %FIRFilterStreaming.exit ]
  store i32 %40, i32* %11, align 4, !tbaa !1
  store i32 %39, i32* %10, align 4, !tbaa !1
  store i32 %38, i32* %12, align 4, !tbaa !1
  store i32 %37, i32* %13, align 4, !tbaa !1
  store i32 %36, i32* %14, align 4, !tbaa !1
  store i32 %35, i32* %15, align 4, !tbaa !1
  store i32 %34, i32* %16, align 4, !tbaa !1
  store i32 %33, i32* %17, align 4, !tbaa !1
  store i32 %32, i32* %18, align 4, !tbaa !1
  store i32 %31, i32* %19, align 4, !tbaa !1
  store i32 %30, i32* %20, align 4, !tbaa !1
  store i32 %29, i32* %21, align 4, !tbaa !1
  store i32 %28, i32* %22, align 4, !tbaa !1
  store i32 %27, i32* %23, align 4, !tbaa !1
  store i32 %26, i32* %24, align 4, !tbaa !1
  store i32 %i.01, i32* %9, align 4, !tbaa !1
  %41 = icmp eq i32 %40, 0
  br i1 %41, label %FIRFilterStreaming.exit, label %.preheader.i

.preheader.i:                                     ; preds = %.preheader.i, %25
  %j.02.i = phi i32 [ %49, %.preheader.i ], [ 0, %25 ]
  %temp.01.i = phi i32 [ %48, %.preheader.i ], [ 0, %25 ]
  %42 = sub i32 15, %j.02.i
  %43 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 %42
  %44 = load i32* %43, align 4, !tbaa !1
  %45 = getelementptr inbounds [16 x i32]* @main.coefficients, i32 0, i32 %j.02.i
  %46 = load i32* %45, align 4, !tbaa !1
  %47 = mul nsw i32 %46, %44
  %48 = add nsw i32 %47, %temp.01.i
  %49 = add nsw i32 %j.02.i, 1
  %exitcond.i = icmp eq i32 %49, 16
  br i1 %exitcond.i, label %FIRFilterStreaming.exit, label %.preheader.i

FIRFilterStreaming.exit:                          ; preds = %.preheader.i, %25
  %.0.i = phi i32 [ 0, %25 ], [ %48, %.preheader.i ]
  %50 = add i32 %.0.i, %total.02
  %51 = add nsw i32 %i.01, 1
  %exitcond = icmp eq i32 %51, 33
  br i1 %exitcond, label %52, label %25

; <label>:52                                      ; preds = %FIRFilterStreaming.exit
  %.lcssa8 = phi i32 [ %50, %FIRFilterStreaming.exit ]
  %53 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([12 x i8]* @.str, i32 0, i32 0), i32 %.lcssa8) #1
  %54 = icmp eq i32 %.lcssa8, 44880
  br i1 %54, label %55, label %57

; <label>:55                                      ; preds = %52
  %56 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str1, i32 0, i32 0)) #1
  br label %59

; <label>:57                                      ; preds = %52
  %58 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str2, i32 0, i32 0)) #1
  br label %59

; <label>:59                                      ; preds = %57, %55
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
