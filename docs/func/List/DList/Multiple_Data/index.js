// DList_M 文档页面脚本
document.addEventListener('DOMContentLoaded', function() {
    if (typeof Prism !== 'undefined') {
        Prism.highlightAll();
    } else {
        setTimeout(function() {
            if (typeof Prism !== 'undefined') {
                Prism.highlightAll();
            }
        }, 500);
    }

    const signatures = document.querySelectorAll('.funcSignature');
    signatures.forEach((sig, index) => {
        sig.style.opacity = '0';
        sig.style.transform = 'translateX(-10px)';
        setTimeout(() => {
            sig.style.transition = 'all 0.3s ease';
            sig.style.opacity = '1';
            sig.style.transform = 'translateX(0)';
        }, 50 * index);
    });
});