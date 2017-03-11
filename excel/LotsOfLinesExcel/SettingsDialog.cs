using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LotsOfLinesExcel
{
    public partial class SettingsDialog : Form
    {
        public SettingsDialog()
        {
            InitializeComponent();

            //Init line edit from settings
            lotsOfLinesPathEdit.Text = Properties.Settings.Default.LotsOfLinesPath;
        }

        private void browseButton_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            dlg.ShowDialog();

            //Store selected path
            if (dlg.SelectedPath != null)
            {
                lotsOfLinesPathEdit.Text = dlg.SelectedPath;
            }
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            //Save settings before closing dialog
            Properties.Settings.Default.LotsOfLinesPath = lotsOfLinesPathEdit.Text;
            Properties.Settings.Default.Save();
            Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
