// FOCX 主页脚本
document.addEventListener('DOMContentLoaded', function() {
    // 等待 Prism.js 加载完成后手动高亮
    if (typeof Prism !== 'undefined') {
        Prism.highlightAll();
    } else {
        setTimeout(function() {
            if (typeof Prism !== 'undefined') {
                Prism.highlightAll();
            }
        }, 500);
    }
});