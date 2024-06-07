document.addEventListener('DOMContentLoaded', function () {
    const navItems = document.querySelectorAll('.li_nav');
    const contentDiv = document.getElementById('div_content');

    const contents = {
        content1: `
        <ul id="ul_game">
        <li class="li_game" id="time">07:00PM</li>
        <li class="li_game" id="team">Buffalo Bills</li>
        <li class="li_game" id="logo"><img id="img_team" src="img/Buffalo Bills.png" alt="Logo">
        </li>
        <li class="li_game" id="at">@</li>
        <li class="li_game" id="logo"><img id="img_team" src="img/Chicago Bears.png" alt="Logo">
        </li>
        <li class="li_game" id="team">Chicago Bears</li>
        <li class="li_game" id="watch">Full</li>
        <li class="li_game" id="seen">yes</li>
        </ul>
        `,
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
