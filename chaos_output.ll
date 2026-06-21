; ModuleID = 'chaos_output'
source_filename = "chaos_output"

@s = private unnamed_addr constant [18 x i8] c"=== 1. \EB\B3\80\EC\88\98 ===\00", align 1
@0 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@s.1 = private unnamed_addr constant [6 x i8] c"Chaos\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@2 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@3 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@4 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@s.2 = private unnamed_addr constant [18 x i8] c"=== 2. \EC\97\B0\EC\82\B0 ===\00", align 1
@5 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@6 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@7 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@8 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@9 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@10 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@11 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@s.3 = private unnamed_addr constant [18 x i8] c"=== 3. \EC\8B\A4\EC\88\98 ===\00", align 1
@12 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@13 = private unnamed_addr constant [4 x i8] c"%g\0A\00", align 1
@14 = private unnamed_addr constant [4 x i8] c"%g\0A\00", align 1
@15 = private unnamed_addr constant [4 x i8] c"%g\0A\00", align 1
@s.4 = private unnamed_addr constant [21 x i8] c"=== 4. \EA\B5\AC\EC\A1\B0\EC\B2\B4 ===\00", align 1
@16 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@s.5 = private unnamed_addr constant [5 x i8] c"Home\00", align 1
@17 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@18 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@s.6 = private unnamed_addr constant [18 x i8] c"=== 5. concat ===\00", align 1
@19 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@s.7 = private unnamed_addr constant [7 x i8] c"Hello \00", align 1
@s.8 = private unnamed_addr constant [6 x i8] c"World\00", align 1
@20 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@21 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@s.9 = private unnamed_addr constant [16 x i8] c"=== 6. sqrt ===\00", align 1
@22 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@23 = private unnamed_addr constant [4 x i8] c"%g\0A\00", align 1
@s.10 = private unnamed_addr constant [15 x i8] c"=== 7. abs ===\00", align 1
@24 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@25 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@s.11 = private unnamed_addr constant [21 x i8] c"=== 8. factorial ===\00", align 1
@26 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@27 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@s.12 = private unnamed_addr constant [22 x i8] c"=== 9. \ED\8C\8C\EC\9D\BC I/O ===\00", align 1
@28 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@s.13 = private unnamed_addr constant [11 x i8] c"all100.txt\00", align 1
@s.14 = private unnamed_addr constant [4 x i8] c"OK!\00", align 1
@29 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@s.15 = private unnamed_addr constant [11 x i8] c"all100.txt\00", align 1
@30 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@31 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@s.16 = private unnamed_addr constant [23 x i8] c"=== \EC\A0\84\EB\B6\80 \EC\99\84\EB\A3\8C! ===\00", align 1
@32 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

declare i32 @scanf(ptr, ...)

declare i64 @strlen(ptr)

declare ptr @malloc(i64)

declare ptr @strcpy(ptr, ptr)

declare ptr @strcat(ptr, ptr)

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.pow.f64(double, double) #0

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.sqrt.f64(double) #0

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.sin.f64(double) #0

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.cos.f64(double) #0

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.log.f64(double) #0

declare ptr @fopen(ptr, ptr)

declare i64 @fread(ptr, i64, i64, ptr)

declare i64 @fwrite(ptr, i64, i64, ptr)

declare i32 @fclose(ptr)

define i64 @abs(i64 %0) {
e:
  %n = alloca i64, align 8
  store i64 %0, ptr %n, align 4
  %v = load i64, ptr %n, align 4
  %l = icmp slt i64 %v, 0
  %1 = zext i1 %l to i64
  %2 = icmp ne i64 %1, 0
  br i1 %2, label %t, label %e1

t:                                                ; preds = %e
  %v2 = load i64, ptr %n, align 4
  %sub = sub i64 0, %v2
  ret i64 %sub

e1:                                               ; preds = %e
  br label %m

m:                                                ; preds = %e1
  %v3 = load i64, ptr %n, align 4
  ret i64 %v3
}

define i64 @max(i64 %0, i64 %1) {
e:
  %a = alloca i64, align 8
  store i64 %0, ptr %a, align 4
  %b = alloca i64, align 8
  store i64 %1, ptr %b, align 4
  %v = load i64, ptr %a, align 4
  %v1 = load i64, ptr %b, align 4
  %g = icmp sgt i64 %v, %v1
  %2 = zext i1 %g to i64
  %3 = icmp ne i64 %2, 0
  br i1 %3, label %t, label %e2

t:                                                ; preds = %e
  %v3 = load i64, ptr %a, align 4
  ret i64 %v3

e2:                                               ; preds = %e
  br label %m

m:                                                ; preds = %e2
  %v4 = load i64, ptr %b, align 4
  ret i64 %v4
}

define i64 @min(i64 %0, i64 %1) {
e:
  %a = alloca i64, align 8
  store i64 %0, ptr %a, align 4
  %b = alloca i64, align 8
  store i64 %1, ptr %b, align 4
  %v = load i64, ptr %a, align 4
  %v1 = load i64, ptr %b, align 4
  %l = icmp slt i64 %v, %v1
  %2 = zext i1 %l to i64
  %3 = icmp ne i64 %2, 0
  br i1 %3, label %t, label %e2

t:                                                ; preds = %e
  %v3 = load i64, ptr %a, align 4
  ret i64 %v3

e2:                                               ; preds = %e
  br label %m

m:                                                ; preds = %e2
  %v4 = load i64, ptr %b, align 4
  ret i64 %v4
}

define i64 @pow(i64 %0, i64 %1) {
e:
  %base = alloca i64, align 8
  store i64 %0, ptr %base, align 4
  %exp = alloca i64, align 8
  store i64 %1, ptr %exp, align 4
  %result = alloca i64, align 8
  store i64 1, ptr %result, align 4
  %i = alloca i64, align 8
  store i64 0, ptr %i, align 4
  br label %wc

wc:                                               ; preds = %wb, %e
  %sv = load i64, ptr %i, align 4
  %v = load i64, ptr %exp, align 4
  %l = icmp slt i64 %sv, %v
  %2 = zext i1 %l to i64
  %3 = icmp ne i64 %2, 0
  br i1 %3, label %wb, label %we

wb:                                               ; preds = %wc
  %sv1 = load i64, ptr %result, align 4
  %v2 = load i64, ptr %base, align 4
  %mul = mul i64 %sv1, %v2
  store i64 %mul, ptr %result, align 4
  %sv3 = load i64, ptr %i, align 4
  %add = add i64 %sv3, 1
  store i64 %add, ptr %i, align 4
  br label %wc

we:                                               ; preds = %wc
  %sv4 = load i64, ptr %result, align 4
  ret i64 %sv4
}

define i64 @factorial(i64 %0) {
e:
  %n = alloca i64, align 8
  store i64 %0, ptr %n, align 4
  %v = load i64, ptr %n, align 4
  %le = icmp sle i64 %v, 1
  %1 = zext i1 %le to i64
  %2 = icmp ne i64 %1, 0
  br i1 %2, label %t, label %e1

t:                                                ; preds = %e
  ret i64 1

e1:                                               ; preds = %e
  br label %m

m:                                                ; preds = %e1
  %v2 = load i64, ptr %n, align 4
  %v3 = load i64, ptr %n, align 4
  %sub = sub i64 %v3, 1
  %3 = call i64 @factorial(i64 %sub)
  %mul = mul i64 %v2, %3
  ret i64 %mul
}

define i64 @double(i64 %0) {
e:
  %n = alloca i64, align 8
  store i64 %0, ptr %n, align 4
  %v = load i64, ptr %n, align 4
  %mul = mul i64 %v, 2
  ret i64 %mul
}

define i64 @main() {
e:
  %0 = call i32 (ptr, ...) @printf(ptr @0, ptr @s)
  %a = alloca i64, align 8
  store i64 42, ptr %a, align 4
  %b = alloca ptr, align 8
  store ptr @s.1, ptr %b, align 8
  %c = alloca i1, align 1
  store i1 true, ptr %c, align 1
  %l = alloca { ptr, i64, i64 }, align 8
  %1 = alloca i64, i64 100, align 8
  %2 = getelementptr inbounds [100 x i64], ptr %1, i32 0, i32 0
  store i64 1, ptr %2, align 4
  %3 = getelementptr inbounds [100 x i64], ptr %1, i32 0, i32 1
  store i64 2, ptr %3, align 4
  %4 = getelementptr inbounds [100 x i64], ptr %1, i32 0, i32 2
  store i64 3, ptr %4, align 4
  %5 = getelementptr inbounds { ptr, i64, i64 }, ptr %l, i32 0, i32 1
  store i64 3, ptr %5, align 4
  %6 = getelementptr inbounds { ptr, i64, i64 }, ptr %l, i32 0, i32 2
  store i64 100, ptr %6, align 4
  %7 = getelementptr inbounds { ptr, i64, i64 }, ptr %l, i32 0, i32 0
  store ptr %1, ptr %7, align 8
  %d = alloca { ptr, i64, i64 }, align 8
  %sv = load i64, ptr %a, align 4
  %8 = call i32 (ptr, ...) @printf(ptr @1, i64 %sv)
  %sv1 = load ptr, ptr %b, align 8
  %9 = call i32 (ptr, ...) @printf(ptr @2, ptr %sv1)
  %sv2 = load i1, ptr %c, align 1
  %10 = zext i1 %sv2 to i64
  %11 = call i32 (ptr, ...) @printf(ptr @3, i64 %10)
  %12 = getelementptr inbounds { ptr, i64, i64 }, ptr %l, i32 0, i32 0
  %13 = load ptr, ptr %12, align 8
  %14 = getelementptr i64, ptr %13, i64 0
  %15 = load i64, ptr %14, align 4
  %16 = call i32 (ptr, ...) @printf(ptr @4, i64 %15)
  %17 = call i32 (ptr, ...) @printf(ptr @5, ptr @s.2)
  %18 = call i32 (ptr, ...) @printf(ptr @6, i64 15)
  %19 = call i32 (ptr, ...) @printf(ptr @7, i64 12)
  %20 = call i32 (ptr, ...) @printf(ptr @8, i64 42)
  %21 = call i32 (ptr, ...) @printf(ptr @9, i64 25)
  %22 = call i32 (ptr, ...) @printf(ptr @10, i64 4)
  %23 = call double @llvm.pow.f64(double 2.000000e+00, double 1.000000e+01)
  %24 = fptosi double %23 to i64
  %25 = call i32 (ptr, ...) @printf(ptr @11, i64 %24)
  %26 = call i32 (ptr, ...) @printf(ptr @12, ptr @s.3)
  %x = alloca double, align 8
  store double 3.140000e+00, ptr %x, align 8
  %y = alloca double, align 8
  store double 2.500000e+00, ptr %y, align 8
  %sv3 = load double, ptr %x, align 8
  %sv4 = load double, ptr %y, align 8
  %fadd = fadd double %sv3, %sv4
  %z = alloca double, align 8
  store double %fadd, ptr %z, align 8
  %sv5 = load double, ptr %x, align 8
  %27 = call i32 (ptr, ...) @printf(ptr @13, double %sv5)
  %sv6 = load double, ptr %y, align 8
  %28 = call i32 (ptr, ...) @printf(ptr @14, double %sv6)
  %sv7 = load double, ptr %z, align 8
  %29 = call i32 (ptr, ...) @printf(ptr @15, double %sv7)
  %30 = call i32 (ptr, ...) @printf(ptr @16, ptr @s.4)
  %st = alloca { i64, i64, ptr }, align 8
  %31 = getelementptr inbounds { i64, i64, ptr }, ptr %st, i32 0, i32 0
  store i64 10, ptr %31, align 4
  %32 = getelementptr inbounds { i64, i64, ptr }, ptr %st, i32 0, i32 1
  store i64 20, ptr %32, align 4
  %33 = getelementptr inbounds { i64, i64, ptr }, ptr %st, i32 0, i32 2
  store ptr @s.5, ptr %33, align 8
  %sv8 = load { i64, i64, ptr }, ptr %st, align 8
  %p = alloca { i64, i64, ptr }, align 8
  store { i64, i64, ptr } %sv8, ptr %p, align 8
  %34 = getelementptr inbounds { i64, i64, ptr }, ptr %p, i32 0, i32 0
  %35 = load i64, ptr %34, align 4
  %36 = call i32 (ptr, ...) @printf(ptr @17, i64 %35)
  %37 = getelementptr inbounds { i64, i64, ptr }, ptr %p, i32 0, i32 2
  %38 = load ptr, ptr %37, align 8
  %39 = call i32 (ptr, ...) @printf(ptr @18, ptr %38)
  %40 = call i32 (ptr, ...) @printf(ptr @19, ptr @s.6)
  %s1 = alloca ptr, align 8
  store ptr @s.7, ptr %s1, align 8
  %s2 = alloca ptr, align 8
  store ptr @s.8, ptr %s2, align 8
  %sv9 = load ptr, ptr %s1, align 8
  %sv10 = load ptr, ptr %s2, align 8
  %41 = call i64 @strlen(ptr %sv9)
  %42 = call i64 @strlen(ptr %sv10)
  %43 = add i64 %41, %42
  %44 = add i64 %43, 1
  %45 = call ptr @malloc(i64 %44)
  %46 = call ptr @strcpy(ptr %45, ptr %sv9)
  %47 = call ptr @strcat(ptr %45, ptr %sv10)
  %48 = call i32 (ptr, ...) @printf(ptr @20, ptr %45)
  %sv11 = load ptr, ptr %s1, align 8
  %sv12 = load ptr, ptr %s2, align 8
  %49 = call i64 @strlen(ptr %sv11)
  %50 = call i64 @strlen(ptr %sv12)
  %51 = add i64 %49, %50
  %52 = add i64 %51, 1
  %53 = call ptr @malloc(i64 %52)
  %54 = call ptr @strcpy(ptr %53, ptr %sv11)
  %55 = call ptr @strcat(ptr %53, ptr %sv12)
  %56 = call i32 (ptr, ...) @printf(ptr @21, ptr %53)
  %57 = call i32 (ptr, ...) @printf(ptr @22, ptr @s.9)
  %58 = call double @llvm.sqrt.f64(double 1.600000e+01)
  %59 = call i32 (ptr, ...) @printf(ptr @23, double %58)
  %60 = call i32 (ptr, ...) @printf(ptr @24, ptr @s.10)
  %61 = call i64 @abs(i64 -99)
  %62 = call i32 (ptr, ...) @printf(ptr @25, i64 %61)
  %63 = call i32 (ptr, ...) @printf(ptr @26, ptr @s.11)
  %64 = call i64 @factorial(i64 5)
  %65 = call i32 (ptr, ...) @printf(ptr @27, i64 %64)
  %66 = call i32 (ptr, ...) @printf(ptr @28, ptr @s.12)
  %67 = call ptr @fopen(ptr @s.13, ptr @29)
  %68 = call i64 @strlen(ptr @s.14)
  %69 = call i64 @fwrite(ptr @s.14, i64 1, i64 %68, ptr %67)
  %70 = call i32 @fclose(ptr %67)
  %71 = call ptr @fopen(ptr @s.15, ptr @30)
  %72 = call ptr @malloc(i64 4096)
  %73 = call i64 @fread(ptr %72, i64 1, i64 4096, ptr %71)
  %74 = call i32 @fclose(ptr %71)
  %75 = call i32 (ptr, ...) @printf(ptr @31, ptr %72)
  %76 = call i32 (ptr, ...) @printf(ptr @32, ptr @s.16)
  ret i64 0
}

declare i32 @printf(ptr, ...)

attributes #0 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
