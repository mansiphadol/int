% Facts about diseases
disease(flu).
disease(cold).
disease(pneumonia).

% Symptoms associated with diseases
symptom(flu, fever).
symptom(flu, cough).
symptom(cold, runny_nose).
symptom(cold, sneezing).
symptom(pneumonia, high_fever).
symptom(pneumonia, shortness_of_breath).

% Rules for diagnosing diseases based on symptoms
diagnose(Disease) :-
    symptom(Disease, Symptom1),
    symptom(Disease, Symptom2),
    Symptom1 = fever,
    Symptom2 = cough.


    # queries
    # disease(Disease).
    # symptom(flu, Symptom).
    # symptom(Disease, fever).
    # diagnose(flu).
    # diagnose(pneumonia).
    #  symptom(Disease, cough).

