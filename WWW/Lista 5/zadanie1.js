'use strict';
// ustawienia
var width = 500; // "margines przesunięcia"
var animationSpeed = 1000; // czas przejścia
var pause = 1000; // czas pomiędzy przejściami
var currentSlide = 1; // początek

$(function() 
{
    var $sliderbar = $( "#slider-range-max" ).slider({
        range: "max",
        min: 1,
        max: 5,
        value: 2,
        slide: function( event, ui ) 
        {
          pause = ui.value * 1000;
          $( "#amount" ).val( ui.value );
        }
    });

    $( "#amount" ).val( $( "#slider-range-max" ).slider( "value" ) );
});

$(function()
{
    var $slider = $('#sliderContainer');
    var $slideContainer = $slider.find('.slides');
    var $slides = $slider.find('.slide');
    var interval;

    function startSlider() 
    {
        interval = setInterval(function()
        {
            $slideContainer.animate({'margin-left': '-='+width}, animationSpeed, function()
            {
                if (++currentSlide === $slides.length) 
                {
                    currentSlide = 1;
                    $slideContainer.css('margin-left', 0);
                }
            });
        }, pause);
    }

    function pauseSlider() 
    {
        clearInterval(interval);
    }

    $slideContainer
        .on('mouseenter', pauseSlider)
        .on('mouseleave', startSlider);

    startSlider();
});