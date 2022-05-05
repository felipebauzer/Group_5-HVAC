//SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 <0.8.0; 
contract HVAC{
    //GetTemperature

  uint idDigits = 16; 
  uint idModulus = 10 ** idDigits; 
 
 function _generateValueId(string memory _str) private view
    returns (uint) {
        uint rand = uint (keccak256(abi.encodePacked(_str)));
       return (rand%idModulus);
    }

    function Value(string memory _Parameter, uint _degree) public {

        uint randId=_generateValueId(_Parameter);

        degree[randId] = _degree;

        validationTemp(randId);  

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

}
