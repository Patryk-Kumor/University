$(function () 
{
    var dialog, form,
        name = $("#name"),
        surname = $("#surname"),
        city = $("#city"),
        cityCode = $("#cityCode"),
        date = $("#date"),
        allFields = $([]).add(name).add(surname).add(city).add(cityCode).add(date),
        tips = $(".validateTips");

    function updateTips(t) 
    {
        tips
            .text(t)
            .addClass("ui-state-highlight");
        setTimeout(function () 
        {
            tips.removeClass("ui-state-highlight", 1500);
        }, 500);
    }
    function checkLength(o, n, min, max)
    {
        if (o.val().length > max || o.val().length < min) {
            o.addClass("ui-state-error");
            updateTips("Długość " + n + " musi być pomiędzy " +
                    min + " a " + max + ".");
            return false;
        } else 
        {
            return true;
        }
    }
    function checkRegexp(o, regexp, n) 
    {
        if (!( regexp.test(o.val()) )) 
        {
            o.addClass("ui-state-error");
            updateTips(n);
            return false;
        } else 
        {
            return true;
        }
    }  

    function addUser()
     {
        allFields.removeClass("ui-state-error");
        var valid = true;
        valid = valid && checkLength(name, "imienia", 3, 40);
        valid = valid && checkLength(surname, "nazwiska", 3, 40);
        valid = valid && checkLength(city, "miasta", 3, 40);
        valid = valid && checkLength(cityCode, "kodu pocztowego", 6, 6);
        valid = valid && checkRegexp(name, /[A-ZĄĘŁŃÓŚŹŻ][a-ząćęłńóśźż]*$/i, "Imię musi składać się ze znaków a-z lub spacji oraz zaczynać się literą");
        valid = valid && checkRegexp(surname, /[A-ZĄĘŁŃÓŚŹŻ][a-ząćęłńóśźż]*$/i, "Nazwisko musi składać się ze znaków a-z lub spacji oraz zaczynać się literą");
        valid = valid && checkRegexp(cityCode, /^[0-9]{2}-[0-9]{3}/i, "Kod pocztowy musi mieć format xx-xxx i składać się z cyfr i myślnika");
        valid = valid && checkRegexp(date, /^[0-9]{2}-[0-9]{2}-[1-2]{1}[0-9]{1}[0-9]{1}[0-9]{1}/i, "Data urodzin musi być w postaci DD-MM-RRRR");
        if (valid) 
        {
            $("#users tbody").append( "<tr>" +
                "<td>" + name.val() + "</td>" +
                "<td>" + surname.val() + "</td>" +
                "<td>" + city.val() + "</td>" +
                "<td>" + cityCode.val() + "</td>" +
                "<td>" + date.val() + "</td>" +
                "<td>" + "<button type='button'  class='removebutton' title='Usuń'>X</button>" + "</td>" + "</tr>");
            $(this).dialog("close");
        }
        return valid;
    };

    dialog = $("#dialog-form").dialog({
        autoOpen: false,
        height: 500,
        width: 600,
        modal: true,
        buttons: 
        {
            "Dodaj": addUser,
            "Anuluj": function () 
            {
                dialog.dialog("close");
            }
        },
        close: function () 
        {
            form[0].reset();
            allFields.removeClass("ui-state-error");
        }
    });

    form = dialog.find("form").on("submit", function (event) 
    {
        event.preventDefault();
        addUser();
    });

    $("#create-user").button().on("click", function () 
    {
        dialog.dialog("open");
    });

    $("#date").datepicker({
        dateFormat: 'dd-mm-yy'
    });

    $(document).on('click', 'button.removebutton', function () 
    {
        $("#dialog-remove").dialog('open');
        $(this).closest('tr').addClass('toRemove');
        return false;
    });

    $("#dialog-remove").dialog({
        modal: true,
        width: 450,
        height: 250,
        autoOpen: false,
        buttons: 
        {
            "Tak": function () 
            {
                $(".toRemove").remove();
                $(this).dialog("close");
            },
            "Nie": function ()
            {
                $(".toRemove").removeClass("toRemove");
                $(this).dialog("close");
            }
        }
    });
});

