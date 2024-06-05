document.addEventListener('DOMContentLoaded', function () {
    const navItems = document.querySelectorAll('.li_nav');
    const contentDiv = document.getElementById('div_content');

    const contents = {
        content1: '<h1>Week 1</h1><p>This is the content for Week 1.</p>',
        content2: '<h1>Week 2</h1><p>This is the content for Week 2.</p>',
        content3: '<h1>Week 3</h1><p>This is the content for Week 3.</p>',
        content4: '<h1>Week 4</h1><p>This is the content for Week 4.</p>'
    };

    navItems.forEach(item => {
        item.addEventListener('click', function () {
            const contentKey = this.getAttribute('data-content');
            contentDiv.innerHTML = contents[contentKey];
        });
    });
});
