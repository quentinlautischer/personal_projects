//#Others content is an unused content slot.

$(document).ready( function(){
//STILL UNDER CONSTRUCTION
    setTimeout(main_function, 1);

});

var  main_function = function(){

    var media_width = $(window).width();

    $(window).resize(function(){
        var new_width = $(window).width();
        if(new_width != media_width){
            waitForFinalEvent(function(){
            location.reload(true);}, 500); 
        }
    });

    if(media_width <= 1000){
        // window width is smaller than 800px (Mobile)
        $("#about_Content").show(); //left
        $("#skills_Content").show(); //up
        $("#projects_Content").show(); //down
        $("#midNav").hide();
        $("#topNav").hide();

    }
    else {
        // window width is greater than 800px (Desktop)
        $('#nav').css({
            position:'absolute',
            left: ($(window).width() - $('#nav').outerWidth())/2,
            top: ($(window).height() - $('#nav').outerHeight())/3
        });

        $("#about_Content").hide(); //left
        $("#skills_Content").hide(); //up
        $("#projects_Content").hide(); //down
        $("#other_Content").hide(); //right

        var last_Nav_Move;

        var fix_Nav = function(direction){
            $("#" + direction + "Arrow").css("color", "#FFFFFF");
            switch(direction)
            {
                case "left":
                    document.getElementById("about_Content").style.top = 0;
                    clearTimeout(gCreditsInterval);
                    $("#about_Content").hide();
                    $('#nav').animate({left: ($(window).width() - $('#nav').outerWidth())/2},500);
                    break;
                case "right":

                    $("#other_Content").hide();
                    $('#nav').animate({left: ($(window).width() - $('#nav').outerWidth())/2},500);
                    break;
                case "up":
                    $("#skills_Content").hide();
                    $('#nav').animate({top: ($(window).height() - $('#nav').outerHeight())/2},500);
                    break;
                case "down":

                    $("#projects_Content").hide();
                    $('#nav').animate({top: ($(window).height() - $('#nav').outerHeight())/2},500);
                    break;
                default:
                    break;
            }
        }

        $('#downArrow').click( function(){
            $('#nav').finish();
            fix_Nav(last_Nav_Move);
            var pos = 2*(($(window).height() - $('#nav').outerHeight())/2);
            $(this).css("color", "#00AAAA");
            $('#nav').animate({top: +pos-50},1000, function(){
                $("#projects_Content").show();
            });
            last_Nav_Move = "down";
        });

        $('#upArrow').click( function(){
            $('#nav').finish();
            fix_Nav(last_Nav_Move);
            $(this).css("color", "#00AAAA");
            $('#nav').animate({top: 0+50},1000,function(){
                $("#skills_Content").show();
            });
            last_Nav_Move = "up";
        });

        $('#rightArrow').click( function(){
            $('#nav').finish();
            fix_Nav(last_Nav_Move);
            var pos = $(window).width()-$('#nav').width();
            $(this).css("color", "#00AAAA");
            $('#nav').animate({left: +pos-50},1000,function(){
                $("#other_Content").show();
            });
            last_Nav_Move = "right";
        });

        $('#leftArrow').click( function(){
            $('#nav').finish();
            fix_Nav(last_Nav_Move);
            pos = ($('#nav').width()-$('#subNav').width())/2;
            $(this).css("color", "#00AAAA");
            $('#nav').animate({left: -pos+50},1000,function(){
                $("#about_Content").show();
                init_about_scroll();
            });
            last_Nav_Move = "left";
        });

        $('#midNav').click( function(){
            document.getElementById("about_Content").style.top = 0;
            clearTimeout(gCreditsInterval);
            $('#nav').finish();
            fix_Nav(last_Nav_Move);
            last_Nav_Move = "";
            $("#about_Content").hide(); //left
            $("#skills_Content").hide(); //up
            $("#projects_Content").hide(); //down
            $("#other_Content").hide(); //right

        })

        $('#bg').click( function(){
            document.getElementById("about_Content").style.top = 0;
            clearTimeout(gCreditsInterval);
            $('#nav').finish();
            fix_Nav(last_Nav_Move);
            last_Nav_Move = "";
            $("#about_Content").hide(); //left
            $("#skills_Content").hide(); //up
            $("#projects_Content").hide(); //down
            $("#other_Content").hide(); //right


        })

    }
}

//http://stackoverflow.com/questions/2854407/javascript-jquery-window-resize-how-to-fire-after-the-resize-is-completed
var waitForFinalEvent = (function(){
  var timers = {}; 
  return function (callback, ms, uniqueId){
    if (!uniqueId) {
     uniqueId = "Don't call this twice without a uniqueId";
    }
      if (timers[uniqueId]){
        clearTimeout (timers[uniqueId]);
      } timers[uniqueId] = setTimeout(callback, ms);
  }; 
})();

function init_about_scroll(){
    var cb = document.getElementById("about_Content");
    setTimeout("runCredits()", 1000); 
}

function runCredits(){
    gCreditsInterval = setInterval("creditsCallBack()", 50);
}

function creditsCallBack(){
    var cb = document.getElementById("about_Content"); 
    var newtop = cb.offsetTop - 1; 
    if (newtop>-(document.getElementById("about_scroll").offsetHeight*2)) cb.style.top = newtop+'px';
    else clearTimeout(gCreditsInterval); 
}






