window.onload = (function() {
  
    let i = 1;

    setInterval(() => {
        
        switch (i) {
            case 1:
                document.getElementById('colors').classList.remove('color1')
                document.getElementById('colors').classList.remove('color2')
                document.getElementById('colors').classList.remove('color3')
                document.getElementById('colors').classList.add('color1')
                ++i
                break;
            case 2:
                document.getElementById('colors').classList.remove('color1')
                document.getElementById('colors').classList.remove('color2')
                document.getElementById('colors').classList.remove('color3')
                document.getElementById('colors').classList.add('color2')
                ++i
                break;
            case 3:
                i = 1
                document.getElementById('colors').classList.remove('color1')
                document.getElementById('colors').classList.remove('color2')
                document.getElementById('colors').classList.remove('color3')
                document.getElementById('colors').classList.add('color3')
                break;
        }

    }, 500);

})