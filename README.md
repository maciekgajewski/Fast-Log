Example logg system using variadic templates and compile-time string parsing.

This function:

```
void log2(double d, int x)
{
	LOG("Hello myInt=% myChar=% myDouble=%", x, 'a', d);
}
```

compiles into

```
        pushq   %rbx
        movl    %edi, %ebx
        movl    $37, %edi
        subq    $16, %rsp
        movsd   %xmm0, 8(%rsp)
        call    Logger::Detail::GetWriteBuffer(int)
        movsd   8(%rsp), %xmm0
        movq    $13, (%rax)
        movq    $.LC6, 8(%rax)
        movq    void Logger::Detail::FormatArgs<int, char, double>(std::basic_ostream<char, std::char_traits<char> >&, char const*, char const*), 16(%rax)
        movl    %ebx, 24(%rax)
        movsd   %xmm0, 29(%rax)
        movb    $97, 28(%rax)
        addq    $16, %rsp
        popq    %rbx
        ret
```

And this one:

```
void log1(const std::string& str, int number)
{
	LOG("str=%, number=%", str, number);
}
```

compiles into:

```
        subq    $24, %rsp
        movl    %esi, 12(%rsp)
        leaq    12(%rsp), %rsi
        call    void Logger::Detail::WriteLog<std::string, int>(char const*, std::string const&, int const&)
        addq    $24, %rsp
        ret
```
Where WriteLog<std::string, int> is:

```
        pushq   %r13
        pushq   %r12
        movq    %rdi, %r12
        pushq   %rbp
        pushq   %rbx
        movq    %rsi, %r13
        subq    $8, %rsp
        movq    8(%rdi), %rax
        leaq    5(%rax), %rbx
        leal    24(%rbx), %edi
        call    Logger::Detail::GetWriteBuffer(int)
        movq    %rbx, (%rax)
        movq    $.LC1, 8(%rax)
        leaq    24(%rax), %rbp
        movq    void Logger::Detail::FormatArgs<std::string, int>(std::ostream&, char const*, char const*), 16(%rax)
        movq    (%r12), %rbx
        movq    %rbp, %rdi
        movq    %rbx, %rsi
        call    strcpy
        movq    %rbx, %rdi
        call    strlen
        movl    0(%r13), %edx
        movl    %edx, 1(%rbp,%rax)
        addq    $8, %rsp
        popq    %rbx
        popq    %rbp
        popq    %r12
        popq    %r13
        ret
        
```
(Quite a lot of push/pops that could be avoided when inlined...)


