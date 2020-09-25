window.onload = function load()
{
	document.getElementById("form").onsubmit = validateForm;
	document.getElementById("form_konto").onblur = validateKonto;
	document.getElementById("form_pesel").onblur = validatePesel;
	document.getElementById("form_data").onblur = validateData;
	document.getElementById("form_email").onblur = validateEmail;
} 

function validateForm()
{
    if (validateKonto() && validatePesel() && validatePesel() && validateData() && validateEmail())
    {
        alert('Dane wysłane');
    }
    else
    {
        alert('Błedne dane');
    }
}
function validateKonto()
{
    var numer_konta = document.getElementById('form_konto');
    var wyr = /^[0-9]{26}/;
    if (wyr.test(numer_konta.value) == false)
    {
        numer_konta.style.border = "2px solid red";
        return false;
    }
    else
    {
        numer_konta.style.border = "2px solid green";
        return true
    }
}
function validatePesel()
{
    var numer_pesel = document.getElementById('form_pesel');
    var wyr = /^[0-9]{11}/;
    if (wyr.test(numer_pesel.value) == false)
    {
        numer_pesel.style.border = "2px solid red";
        return false;
    }
    else
    {
        numer_pesel.style.border = "2px solid green";
        return true
    }
}
function validateData()
{
    var data = document.getElementById('form_data');
    //var wyr = /^-[\d]{4}-[0-9]{1,2}-[0-9]{1,2}/;
    var wyr = /[0-9]{1,4}-((0?[1-9])|(1[0-2]))-((0?[1-9])|([12][0-9])|(3[01]))/;
    if (wyr.test(data.value) == false)
    {
        data.style.border = "2px solid red";
        return false;
    }
    else
    {
        data.style.border = "2px solid green";
        return true
    }
}
function validateEmail()
{
    var email = document.getElementById('form_email');
    var wyr = /^[0-9a-z_.-]+@[0-9a-z.-]+\.[a-z]{2,3}$/i;
    if (wyr.test(email.value) == false)
    {
        email.style.border = "2px solid red";
        return false;
    }
    else
    {
        email.style.border = "2px solid green";
        return true
    }
}