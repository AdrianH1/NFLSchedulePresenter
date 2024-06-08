document.addEventListener('DOMContentLoaded', function () {
    const navItems = document.querySelectorAll('.li_nav');
    const contentDiv = document.getElementById('div_content');

    const contents = {
        week1: `
        <!--401671799--><ul id="ul_game"><li class="li_game" id="time">18:00</li><li class="li_game" id="team">Kansas City Chiefs</li><li class="li_game" id="logo"><img id="img_team" src="img/Kansas City Chiefs.png" alt="team logo"></li><li class="li_game" id="at">@</li><li class="li_game" id="logo"><img id="img_team" src="img/Pittsburgh Steelers.png" alt="team logo"></li><li class="li_game" id="team">Pittsburgh Steelers</li><li class="li_game" id="watch">Full</li><li class="li_game" id="seen">no</li></ul>
        `,
        week2: '<h1>Week 2</h1><p>This is the content for Week 2.</p>',
        week4: '<h1>Week 3</h1><p>This is the content for Week 3.</p>',
        week3: '<h1>Week 4</h1><p>This is the content for Week 4.</p>'
    };

    navItems.forEach(item => {
        item.addEventListener('click', function () {
            const contentKey = this.getAttribute('data-content');
            contentDiv.innerHTML = contents[contentKey];
        });
    });
});
