// creatInfo_Self 文档页面脚本
document.addEventListener('DOMContentLoaded', function() {
    // 等待 Prism.js 加载完成后手动高亮
    if (typeof Prism !== 'undefined') {
        Prism.highlightAll();
    } else {
        // 如果 Prism 未加载，等待一下再尝试
        setTimeout(function() {
            if (typeof Prism !== 'undefined') {
                Prism.highlightAll();
            }
        }, 500);
    }

    // 代码块渐入动画
    const codeBlocks = document.querySelectorAll('.codeBlock');
    codeBlocks.forEach(function(block, index) {
        block.style.opacity = '0';
        block.style.transform = 'translateY(10px)';
        setTimeout(function() {
            block.style.transition = 'all 0.4s ease';
            block.style.opacity = '1';
            block.style.transform = 'translateY(0)';
        }, 100 * index);
    });
});