/* Environnement de test */

module top ( input logic clk, nrst,
	    output logic[7:0] m );

logic [7:0] e;

generateur gen0  (.clk(clk), .nrst(nrst), .e(e));
filtre_moy fltr0 (.clk(clk), .nrst(nrst), .e(e), .m(m));
  
endmodule


/* Le filtre */
module filtre_moy (
       input  logic clk,
       input  logic nrst,
       input  logic [7:0] e,
       output logic [7:0] m
);

// ÉCRIRE VOTRE CODE ICI
  
  logic [7:0] dec0;
  logic [7:0] dec1;
  logic [7:0] dec2;
  logic [7:0] dec3;
  
  always@(posedge clk) begin
    dec3<=dec2;
    dec2<=dec1;
    dec1<=dec0;
    dec0<=e;
  end 
  always@(*) 
    m<=(dec0+dec1+dec2+dec3)>>2;
  end
endmodule


/* genérateur d'échantillons */
module generateur (
       input logic clk,
       input logic nrst,
       output logic [7:0] e
);

logic[1:0] lsb;
logic[5:0] msb;

always@(posedge clk or negedge nrst)
 if(!nrst)
   lsb <= 0;
 else
   lsb <= lsb + 1;

logic [3:0] cpt;
always@(posedge clk or negedge nrst)
 if(!nrst)
 begin
   msb <= 0;
   cpt <= 0;
 end
 else
 begin
   cpt <= cpt + 1;
   if(cpt ==4'hf) msb <= msb + 1;
 end

always@(*)
  e <= {msb,lsb};

endmodule

