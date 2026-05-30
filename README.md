清华计算机考研专业课826，将一些相关内容放在这里。

### 关于 github pages 的配置
我将 github pages 的页面生成逻辑配置成了在主页显示 所有 .md 生成的 .html 文件 + 所有 .cpp 文件的链接。

这样生成的 .cpp 的链接，点开之后，网页上会有中文乱码问题，大致原因是 github pages 功能主要是
为了渲染 .md, .html。静态资源文件（.cpp、图片等）原样输出，不处理内容。
所以虽然有了 .cpp 的链接，但是只是提醒有个代码文件，github pages 的效果不适合看，.cpp 文件要直接看原始仓库。

**后续更新**：之前是通过手动写 index.md 和 _config.yaml, _includes/ 中的配置，使得 jekyll 达到这一效果的。但是今天 llm 大人告诉我可以用 [Quartz](https://quartz.jzhao.xyz/)，非常好用，直接降维打击了(但这里不改了)，使用方式见[链接](https://github.com/plerks/ai-notes/blob/62146dd12a6ded8e7839fc1d3841d0cf96c4aa39/README.md)。