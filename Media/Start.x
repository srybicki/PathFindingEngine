xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame emptyLand_001 {
    FrameTransformMatrix {
       4.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 4.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 2.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // emptyLand_001 mesh
      4;
       1.000000; 1.000000; 0.000000;,
      -1.000000; 1.000000; 0.000000;,
      -1.000000;-1.000000; 0.000000;,
       1.000000;-1.000000; 0.000000;;
      1;
      4;3,2,1,0;;
      MeshNormals { // emptyLand_001 normals
        1;
         0.000000;-0.000000; 1.000000;;
        1;
        4;0,0,0,0;;
      } // End of emptyLand_001 normals
      MeshTextureCoords { // emptyLand_001 UV coordinates
        4;
         0.212848; 0.234982;,
         0.020139; 0.234982;,
         0.020139; 0.428728;,
         0.212848; 0.428728;;
      } // End of emptyLand_001 UV coordinates
      MeshMaterialList { // emptyLand_001 material list
        1;
        1;
        0;
        Material matWhite {
           1.000000; 1.000000; 1.000000; 1.000000;;
           96.078431;
           0.000000; 0.000000; 0.000000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"Map.png";}
        }
      } // End of emptyLand_001 material list
    } // End of emptyLand_001 mesh
  } // End of emptyLand_001
} // End of Root
