function checkAnswer() {

    // religion check
    const radiosReligion = document.getElementsByName("religionTrivia")

    var explainReligion = document.createElement('a');
    explainReligion.href = "https://en.wikipedia.org/wiki/Jedi_census_phenomenon";
    explainReligion.target = "_blank";
    explainReligion.innerHTML = `Read more`;


    let answerReligion = "INCORRET - ANSWER: Jedi"
    let colorReligion = "red"

    for (var i = 0, length = radiosReligion.length; i < length; i++) {
        if (radiosReligion[i].checked) {
            if (radiosReligion[i].value === "jedi") {
                answerReligion = "CORRECT"
                colorReligion = "green"
            }
            break
        }
    }

    let answerReligionElement = document.getElementById("religionTriviaAnswer");
    let explainReligionElement = document.getElementById("religionTriviaExplain");

    answerReligionElement.style.color = colorReligion;
    answerReligionElement.innerHTML = answerReligion;

    explainReligionElement.innerHTML = "";
    explainReligionElement.appendChild(explainReligion);


    // jupiter check

    const radiosJupiter = document.getElementsByName("jupiterTrivia")

    var explainJupiter = document.createElement('a');
    explainJupiter.href = "https://en.wikipedia.org/wiki/Great_Red_Spot";
    explainJupiter.target = "_blank";
    explainJupiter.innerHTML = `Read more`;


    let answerJupiter = "INCORRET - ANSWER: 3"
    let colorJupiter = "red"

    for (var i = 0, length = radiosJupiter.length; i < length; i++) {
        if (radiosJupiter[i].checked) {
            if (radiosJupiter[i].value === "3") {
                answerJupiter = "CORRECT"
                colorJupiter = "green"
            }
            break
        }
    }

    let answerJupiterElement = document.getElementById("jupiterTriviaAnswer");
    let explainJupiterElement = document.getElementById("jupiterTriviaExplain");

    answerJupiterElement.style.color = colorJupiter;
    answerJupiterElement.innerHTML = answerJupiter;

    explainJupiterElement.innerHTML = "";
    explainJupiterElement.appendChild(explainJupiter);

}


function listen(){
    document.querySelector("#answer").addEventListener('click', checkAnswer)
}

document.addEventListener('DOMContentLoaded', listen)