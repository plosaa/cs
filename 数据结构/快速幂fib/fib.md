习题解析1-20

# 用矩阵快速幂求 $fib(n)$

将 $fib(n) = fib(n - 1) + fib(n - 2)$ 写成矩阵的形式：

$$
\begin{bmatrix}
fib(n) \\
fib(n + 1)
\end{bmatrix}

=

\begin{bmatrix}
0 & 1 \\
1 & 1
\end{bmatrix}

\begin{bmatrix}
fib(n - 1) \\
fib(n)
\end{bmatrix}
$$

所以

$$
\begin{bmatrix}
fib(n) \\
fib(n + 1)
\end{bmatrix}

=

\begin{bmatrix}
0 & 1 \\
1 & 1
\end{bmatrix}^n

\begin{bmatrix}
fib(0) \\
fib(1)
\end{bmatrix}

=

\begin{bmatrix}
0 & 1 \\
1 & 1
\end{bmatrix}^n

\begin{bmatrix}
0 \\
1
\end{bmatrix}
$$

然后就可以用矩阵快速幂求 $fib(n)$ 了，时间复杂度 $O(logn)$。

（记住 $fib(0) = 0$ ，老忘记fib的第一项是0还是1）

不过由于 $fib(n) = \theta(\phi^n), \phi = \frac{\sqrt{5} + 1}{2}$ ，位长为 $log(\phi^n)$ ，所以如果 $fib(n)$ 远大于机器字长，运算需要考虑位长的话，打印 $fib(n)$ 的每一位就要 $\theta(n)$ 时间，见习题解析1-20提到的对数代价准则。

---

还有个写法是：

$$
\begin{bmatrix}
fib(n) \\
fib(n - 1)
\end{bmatrix}

=

\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}

\begin{bmatrix}
fib(n - 1) \\
fib(n - 2)
\end{bmatrix}
$$

所以

$$
\begin{bmatrix}
fib(n) \\
fib(n - 1)
\end{bmatrix}

=

\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}^{n - 1}

\begin{bmatrix}
fib(1) \\
fib(0)
\end{bmatrix}

=

\begin{bmatrix}
1 & 1 \\
1 & 0
\end{bmatrix}^{n - 1}

\begin{bmatrix}
1 \\
0
\end{bmatrix}
$$

**[TODO]**: 应该可以用相似对角化证明两种 $fib(n)$ 结果一样。