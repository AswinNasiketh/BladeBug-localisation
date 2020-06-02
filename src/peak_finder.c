//this is the simplest method to find a peak
//mihght need to find a way to get rid of anomaly
Tuple_Q15 peak_finder(q15_t* input, uint16_t size){
    q15_t largest;
    uint16_t index;
    largest = 0;
    index = 0;
    for(uint16_t i = 0; i < size; i++){
        if(input[i] > largest){
            largest = input[i];
            index = i;
        }
    }
    Tuple_Q15 res;
    res.x = index;
    res.y = largest;
    return res;
}