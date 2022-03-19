import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { MpptComponent } from './mppt/mppt.component';
import { BatteryComponent } from './tabs/battery/battery.component';

const routes: Routes = [
    { path: 'battery', component: BatteryComponent },
    {path: 'mppt', component: MpptComponent},
    { path: '**', redirectTo: '/battery', pathMatch: 'full' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
