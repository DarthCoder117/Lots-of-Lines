namespace LotsOfLinesExcel
{
    partial class LotsOfLinesRibbon : Microsoft.Office.Tools.Ribbon.RibbonBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        public LotsOfLinesRibbon()
            : base(Globals.Factory.GetRibbonFactory())
        {
            InitializeComponent();
        }

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lotsOfLinesTab = this.Factory.CreateRibbonTab();
            this.lotsOfLinesGroup = this.Factory.CreateRibbonGroup();
            this.group1 = this.Factory.CreateRibbonGroup();
            this.settingsButton = this.Factory.CreateRibbonButton();
            this.openInLotsOfLinesButton = this.Factory.CreateRibbonButton();
            this.button1 = this.Factory.CreateRibbonButton();
            this.button2 = this.Factory.CreateRibbonButton();
            this.button3 = this.Factory.CreateRibbonButton();
            this.lotsOfLinesTab.SuspendLayout();
            this.lotsOfLinesGroup.SuspendLayout();
            this.group1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lotsOfLinesTab
            // 
            this.lotsOfLinesTab.Groups.Add(this.lotsOfLinesGroup);
            this.lotsOfLinesTab.Groups.Add(this.group1);
            this.lotsOfLinesTab.Label = "Lots Of Lines";
            this.lotsOfLinesTab.Name = "lotsOfLinesTab";
            // 
            // lotsOfLinesGroup
            // 
            this.lotsOfLinesGroup.Items.Add(this.openInLotsOfLinesButton);
            this.lotsOfLinesGroup.Items.Add(this.button1);
            this.lotsOfLinesGroup.Items.Add(this.button2);
            this.lotsOfLinesGroup.Items.Add(this.button3);
            this.lotsOfLinesGroup.Label = "Visualizations";
            this.lotsOfLinesGroup.Name = "lotsOfLinesGroup";
            // 
            // group1
            // 
            this.group1.Items.Add(this.settingsButton);
            this.group1.Label = "Other";
            this.group1.Name = "group1";
            // 
            // settingsButton
            // 
            this.settingsButton.Label = "Settings";
            this.settingsButton.Name = "settingsButton";
            this.settingsButton.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.settingsButton_Click);
            // 
            // openInLotsOfLinesButton
            // 
            this.openInLotsOfLinesButton.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.openInLotsOfLinesButton.Image = global::LotsOfLinesExcel.Properties.Resources.parallel;
            this.openInLotsOfLinesButton.Label = "Parallel Coordinates";
            this.openInLotsOfLinesButton.Name = "openInLotsOfLinesButton";
            this.openInLotsOfLinesButton.ShowImage = true;
            // 
            // button1
            // 
            this.button1.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.button1.Image = global::LotsOfLinesExcel.Properties.Resources.Collocated;
            this.button1.Label = "Colocated Paired Coordinates";
            this.button1.Name = "button1";
            this.button1.ShowImage = true;
            this.button1.Click += new Microsoft.Office.Tools.Ribbon.RibbonControlEventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.button2.Image = global::LotsOfLinesExcel.Properties.Resources.Anchored;
            this.button2.Label = "Radial Paired Coordinates";
            this.button2.Name = "button2";
            this.button2.ShowImage = true;
            // 
            // button3
            // 
            this.button3.ControlSize = Microsoft.Office.Core.RibbonControlSize.RibbonControlSizeLarge;
            this.button3.Image = global::LotsOfLinesExcel.Properties.Resources.Shifted;
            this.button3.Label = "Shifted Paired Coordinates";
            this.button3.Name = "button3";
            this.button3.ShowImage = true;
            // 
            // LotsOfLinesRibbon
            // 
            this.Name = "LotsOfLinesRibbon";
            this.RibbonType = "Microsoft.Excel.Workbook";
            this.Tabs.Add(this.lotsOfLinesTab);
            this.Load += new Microsoft.Office.Tools.Ribbon.RibbonUIEventHandler(this.LotsOfLinesRibbon_Load);
            this.lotsOfLinesTab.ResumeLayout(false);
            this.lotsOfLinesTab.PerformLayout();
            this.lotsOfLinesGroup.ResumeLayout(false);
            this.lotsOfLinesGroup.PerformLayout();
            this.group1.ResumeLayout(false);
            this.group1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        internal Microsoft.Office.Tools.Ribbon.RibbonTab lotsOfLinesTab;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup lotsOfLinesGroup;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton openInLotsOfLinesButton;
        internal Microsoft.Office.Tools.Ribbon.RibbonGroup group1;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton button1;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton button2;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton button3;
        internal Microsoft.Office.Tools.Ribbon.RibbonButton settingsButton;
    }

    partial class ThisRibbonCollection
    {
        internal LotsOfLinesRibbon LotsOfLinesRibbon
        {
            get { return this.GetRibbon<LotsOfLinesRibbon>(); }
        }
    }
}
