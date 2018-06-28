function patch(number) {
  number.prototype.abs = function() {
    return Math.abs(this);
  };

  number.prototype.ceil = function() {
    return Math.ceil(this);
  };

  number.prototype.floor = function() {
    return Math.floor(this);
  };
  
  number.prototype.pow = function(power) {
    return Math.pow(this, power);
  };

  number.prototype.round = function() {
    return Math.round(this);
  };

  number.prototype.trunc = function() {
    return Math.trunc(this);
  };
}

patch(Number);
