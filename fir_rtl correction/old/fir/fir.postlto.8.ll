; ModuleID = 'fir.postlto.8.bc'
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
  call void @legup_memset_4(i8* %1, i8 0, i32 64)
  %2 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 0
  %3 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 14
  %4 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 15
  %5 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 13
  %6 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 12
  %7 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 11
  %8 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 10
  %9 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 9
  %10 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 8
  %11 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 7
  %12 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 6
  %13 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 5
  %14 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 4
  %15 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 3
  %16 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 2
  %17 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 1
  br label %18

; <label>:18                                      ; preds = %FIRFilterStreaming.exit, %0
  %19 = phi i32 [ 0, %0 ], [ %i.01, %FIRFilterStreaming.exit ]
  %20 = phi i32 [ 0, %0 ], [ %19, %FIRFilterStreaming.exit ]
  %21 = phi i32 [ 0, %0 ], [ %20, %FIRFilterStreaming.exit ]
  %22 = phi i32 [ 0, %0 ], [ %21, %FIRFilterStreaming.exit ]
  %23 = phi i32 [ 0, %0 ], [ %22, %FIRFilterStreaming.exit ]
  %24 = phi i32 [ 0, %0 ], [ %23, %FIRFilterStreaming.exit ]
  %25 = phi i32 [ 0, %0 ], [ %24, %FIRFilterStreaming.exit ]
  %26 = phi i32 [ 0, %0 ], [ %25, %FIRFilterStreaming.exit ]
  %27 = phi i32 [ 0, %0 ], [ %26, %FIRFilterStreaming.exit ]
  %28 = phi i32 [ 0, %0 ], [ %27, %FIRFilterStreaming.exit ]
  %29 = phi i32 [ 0, %0 ], [ %28, %FIRFilterStreaming.exit ]
  %30 = phi i32 [ 0, %0 ], [ %29, %FIRFilterStreaming.exit ]
  %31 = phi i32 [ 0, %0 ], [ %30, %FIRFilterStreaming.exit ]
  %32 = phi i32 [ 0, %0 ], [ %31, %FIRFilterStreaming.exit ]
  %33 = phi i32 [ 0, %0 ], [ %32, %FIRFilterStreaming.exit ]
  %total.02 = phi i32 [ 0, %0 ], [ %43, %FIRFilterStreaming.exit ]
  %i.01 = phi i32 [ 1, %0 ], [ %44, %FIRFilterStreaming.exit ]
  store i32 %33, i32* %4, align 4, !tbaa !1
  store i32 %32, i32* %3, align 4, !tbaa !1
  store i32 %31, i32* %5, align 4, !tbaa !1
  store i32 %30, i32* %6, align 4, !tbaa !1
  store i32 %29, i32* %7, align 4, !tbaa !1
  store i32 %28, i32* %8, align 4, !tbaa !1
  store i32 %27, i32* %9, align 4, !tbaa !1
  store i32 %26, i32* %10, align 4, !tbaa !1
  store i32 %25, i32* %11, align 4, !tbaa !1
  store i32 %24, i32* %12, align 4, !tbaa !1
  store i32 %23, i32* %13, align 4, !tbaa !1
  store i32 %22, i32* %14, align 4, !tbaa !1
  store i32 %21, i32* %15, align 4, !tbaa !1
  store i32 %20, i32* %16, align 4, !tbaa !1
  store i32 %19, i32* %17, align 4, !tbaa !1
  store i32 %i.01, i32* %2, align 4, !tbaa !1
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %FIRFilterStreaming.exit, label %.preheader.i

.preheader.i:                                     ; preds = %.preheader.i, %18
  %j.02.i = phi i32 [ %42, %.preheader.i ], [ 0, %18 ]
  %temp.01.i = phi i32 [ %41, %.preheader.i ], [ 0, %18 ]
  %35 = sub i32 15, %j.02.i
  %36 = getelementptr inbounds [16 x i32]* %previous, i32 0, i32 %35
  %37 = load i32* %36, align 4, !tbaa !1
  %38 = getelementptr inbounds [16 x i32]* @main.coefficients, i32 0, i32 %j.02.i
  %39 = load i32* %38, align 4, !tbaa !1
  %40 = mul nsw i32 %39, %37
  %41 = add nsw i32 %40, %temp.01.i
  %42 = add nsw i32 %j.02.i, 1
  %exitcond.i = icmp eq i32 %42, 16
  br i1 %exitcond.i, label %FIRFilterStreaming.exit, label %.preheader.i

FIRFilterStreaming.exit:                          ; preds = %.preheader.i, %18
  %.0.i = phi i32 [ 0, %18 ], [ %41, %.preheader.i ]
  %43 = add i32 %.0.i, %total.02
  %44 = add nsw i32 %i.01, 1
  %exitcond = icmp eq i32 %44, 33
  br i1 %exitcond, label %45, label %18

; <label>:45                                      ; preds = %FIRFilterStreaming.exit
  %.lcssa1 = phi i32 [ %43, %FIRFilterStreaming.exit ]
  %46 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([12 x i8]* @.str, i32 0, i32 0), i32 %.lcssa1) #2
  %47 = icmp eq i32 %.lcssa1, 44880
  br i1 %47, label %48, label %50

; <label>:48                                      ; preds = %45
  %49 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str1, i32 0, i32 0)) #2
  br label %52

; <label>:50                                      ; preds = %45
  %51 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([14 x i8]* @.str2, i32 0, i32 0)) #2
  br label %52

; <label>:52                                      ; preds = %50, %48
  ret i32 %.lcssa1
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) #0

; Function Attrs: nounwind
define internal void @legup_memset_4(i8* %m, i8 zeroext %c1, i32 %n) #1 {
  %1 = alloca i8*, align 4
  %2 = alloca i8, align 1
  %3 = alloca i32, align 4
  %c = alloca i32, align 4
  %s = alloca i32*, align 4
  store i8* %m, i8** %1, align 4
  store i8 %c1, i8* %2, align 1
  store i32 %n, i32* %3, align 4
  %4 = load i8* %2, align 1
  %5 = zext i8 %4 to i32
  store i32 %5, i32* %c, align 4
  %6 = load i32* %c, align 4
  %7 = shl i32 %6, 8
  %8 = load i32* %c, align 4
  %9 = or i32 %8, %7
  store i32 %9, i32* %c, align 4
  %10 = load i32* %c, align 4
  %11 = shl i32 %10, 16
  %12 = load i32* %c, align 4
  %13 = or i32 %12, %11
  store i32 %13, i32* %c, align 4
  %14 = load i8** %1, align 4
  %15 = bitcast i8* %14 to i32*
  store i32* %15, i32** %s, align 4
  %16 = load i32* %3, align 4
  %17 = lshr i32 %16, 2
  store i32 %17, i32* %3, align 4
  br label %18

; <label>:18                                      ; preds = %22, %0
  %19 = load i32* %3, align 4
  %20 = add i32 %19, -1
  store i32 %20, i32* %3, align 4
  %21 = icmp ne i32 %19, 0
  br i1 %21, label %22, label %26

; <label>:22                                      ; preds = %18
  %23 = load i32* %c, align 4
  %24 = load i32** %s, align 4
  %25 = getelementptr inbounds i32* %24, i32 1
  store i32* %25, i32** %s, align 4
  store i32 %23, i32* %24, align 4
  br label %18

; <label>:26                                      ; preds = %18
  ret void
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nobuiltin nounwind }

!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}

!0 = metadata !{metadata !"clang version 3.5.0 (tags/RELEASE_350/final)"}
!1 = metadata !{metadata !2, metadata !2, i64 0}
!2 = metadata !{metadata !"int", metadata !3, i64 0}
!3 = metadata !{metadata !"omnipotent char", metadata !4, i64 0}
!4 = metadata !{metadata !"Simple C/C++ TBAA"}
