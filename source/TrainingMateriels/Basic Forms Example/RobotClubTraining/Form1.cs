using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RobotClubTraining
{
    public partial class frmRobotClub : Form
    {
        public frmRobotClub()
        {
            InitializeComponent();
        }

        private void cmdExample_Click( object sender, EventArgs e )
        {
            lblExample.Text = txtExample.Text;
        }

        private void cmdPersonA_Click(object sender, EventArgs e)
        {
            lblPersonA.Text = txtPersonA.Text;
        }
        
        private void cmdPersonD_Click(object sender, EventArgs e)
        {
            lblPersonD.Text = "Don't press me!"; 
        }

    }
}
