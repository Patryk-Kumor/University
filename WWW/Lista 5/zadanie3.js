$( function()
{

    $(".kwadratColor").draggable({helper: 'clone'});




    $(".kwadrat").droppable({

        
        drop: function(event, ui)
        {
            //alert("upuszczono");

            var droppedItem = $(ui.draggable).css("background-color");
            $(this)
                .css('background-color', droppedItem)
        }
        
    });

});
