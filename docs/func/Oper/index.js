// Oper 模块索引页面脚本
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

    // 卡片动画效果
    const cards = document.querySelectorAll('.operCard');
    cards.forEach((card, index) => {
        card.style.opacity = '0';
        card.style.transform = 'translateY(20px)';
        setTimeout(() => {
            card.style.transition = 'all 0.4s ease';
            card.style.opacity = '1';
            card.style.transform = 'translateY(0)';
        }, 100 * index);
    });
});