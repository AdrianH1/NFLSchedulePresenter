document.addEventListener('DOMContentLoaded', function () {
    const navItems = document.querySelectorAll('.li_nav');
    const contentDiv = document.getElementById('div_content');

    const contents = {
        week1: 'content',
        week2: 'content',
        week3: 'content',
        week4: 'content',
        week5: 'content',
        week6: 'content',
        week7: 'content',
        week8: 'content',
        week9: 'content',
        week10: 'content',
        week11: 'content',
        week12: 'content',
        week13: 'content',
        week14: 'content',
        week15: 'content',
        week16: 'content',
        week17: 'content',
        week18: 'content'
    };

    navItems.forEach(item => {
        item.addEventListener('click', function () {
            const contentKey = this.getAttribute('data-content');
            contentDiv.innerHTML = contents[contentKey];
        });
    });
});
