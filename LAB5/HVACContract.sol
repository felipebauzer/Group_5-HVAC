//SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 <0.8.0; 
contract HVAC{
    
 //Get Temperature
    function Temperature( uint _degree) public {

        uint randId;

        degree[randId] = _degree;

        validationTemp(randId);  

    }

     function Humidity( uint _percentage) public {

        uint randId;

        percent[randId] = _percentage;

        validationHum(randId);  

    }

    function CO2( uint _PPM) public {

        uint randId;

        value[randId] = _PPM;

        validationCO(randId);  

    }

    function CO( uint _ppm) public {

        uint randId;

        valuee[randId] = _ppm;

        validationCOO(randId);  

    }

     function validationTemp( uint _valueId) private view HigherThan(25,_valueId){}

    mapping (uint => uint) private degree;  

    modifier HigherThan (uint _degree, uint _valueId) {

        require (degree[_valueId] <= _degree,"TEMPERATURE IS NOT WITHIN ACCEPTABLE RANGE");
           if (degree[_valueId] < 18 ) {
             revert ("TEMPERATURE IS NOT WITHIN ACCEPTABLE RANGE");
        }
        _;

    }

     function validationHum( uint _valueIId) private view HighThan(70,_valueIId){}

    mapping (uint => uint) private percent;  

    modifier HighThan (uint _percentage, uint _valueIId) {

        require (percent[_valueIId] <= _percentage,"HUMIDITY IS NOT WITHIN ACCEPTABLE RANGE");
           if (percent[_valueIId] < 40 ) {
             revert ("HUMIDTY IS NOT WITHIN ACCEPTABLE RANGE");
        }
        _;

    }

     function validationCO( uint _valueII) private view Limit(1000,_valueII){}

    mapping (uint => uint) private value;  

    modifier Limit (uint _PPM, uint _valueII) {

        require (value[_valueII] <= _PPM,"CO2 LEVEL ABOVE THRESHOLD");
    
        _;

    }

    
     function validationCOO( uint _valueI) private view Limi(9,_valueI){}

    mapping (uint => uint) private valuee;  

    modifier Limi (uint _ppm, uint _valueI) {

        require (valuee[_valueI] <= _ppm,"CO LEVEL ABOVE THRESHOLD");
    
        _;

    }

}
